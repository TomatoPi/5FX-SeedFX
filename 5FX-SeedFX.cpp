#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Midi.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>

static constexpr const bool CONFIRM_MIDI_RECEIVE = false;
static constexpr const uint32_t MAIN_LOOP_FRAMETIME = 1;

static daisy::DaisySeed hw;
static sfx::midi::Parser<64, 16> midi_parser;

void channel_0_callback(float* in, float* out, size_t nsamples)
{
  for (size_t i = 0; i < nsamples; ++i) {
    float sample = sfx::Chorus::Process(in[i]);
    out[i] = sfx::Looper::Process(sample);
  }
}

void channel_1_callback(float* in, float* out, size_t nsamples)
{
  for (size_t i = 0; i < nsamples; i++) {
    out[i] = in[i];
  }
}

void AudioCallback(float** in, float** out, size_t size)
{
  channel_0_callback(in[0], out[0], size);
  channel_1_callback(in[1], out[1], size);
}

int main(void)
{
  bool state(false);

  hw.Configure();
  hw.Init();

  daisy::UartHandler uart1;
  uart1.Init();
  uart1.StartRx();

  midi_parser.Init();

  sfx::Chorus::Init(hw.AudioSampleRate());
  sfx::Looper::Init(hw.AudioSampleRate());

  hw.StartAudio(AudioCallback);

  while (1) {
    if (!uart1.RxActive()) {
      uart1.FlushRx();
      uart1.StartRx();
      midi_parser.cur_length = 0;
    }
    while (uart1.Readable()) {
      midi_parser.Parse(uart1.PopRx());
    }
    if (CONFIRM_MIDI_RECEIVE) {
      while (midi_parser.HasNext()) {
        sfx::midi::Event event = midi_parser.NextEvent();
        sfx::midi::RawEvent raw(event);
        uart1.PollTx(&raw.length, 1);
        uart1.PollTx(raw.buffer, raw.length);
      }
    }
    state = !state;
    hw.SetLed(state);
    daisy::System::Delay(MAIN_LOOP_FRAMETIME);
  }
}
