#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Midi.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>

static constexpr const bool CONFIRM_MIDI_RECEIVE = false;
static constexpr const uint32_t MAIN_LOOP_FRAMETIME = 50;

static daisy::DaisySeed hw;
static sfx::midi::Parser<64, 16> midi_parser;
static daisy::RingBuffer<sfx::midi::RawEvent, 16> midi_out_buffer;

void set_pedalboard_led(uint8_t led, bool state)
{
  midi_out_buffer.Write(
    sfx::midi::RawEvent(3, 0xB0 | led, 0x03, state ? 0x7F : 0x00));
}

namespace callbacks
{
  namespace audio
  {
    void channel_0(float* in, float* out, size_t nsamples)
    {
      for (size_t i = 0; i < nsamples; ++i) {
        float sample = sfx::Chorus::Process(in[i]);
        out[i] = sfx::Looper::Process(sample);
      }
    }

    void channel_1(float* in, float* out, size_t nsamples)
    {
      for (size_t i = 0; i < nsamples; i++) {
        out[i] = in[i];
      }
    }
  }

  namespace midi
  {
    void footswitch(uint8_t channel, uint8_t val)
    {
      bool state = 64 <= val;
      switch (channel) {
      case 1:
        if (state) {
          sfx::Chorus::bypass = !sfx::Chorus::bypass;
          set_pedalboard_led(1, !sfx::Chorus::bypass);
        }
        break;
      }
    }
    void control_change(uint8_t channel, uint8_t cc, uint8_t val)
    {
      switch (cc) {
      case 0x04:
        footswitch(channel, val);
        break;
      }
    }

    void events()
    {
      using namespace sfx::midi;
      while (midi_parser.HasNext()) {
        sfx::midi::Event event = midi_parser.NextEvent();
        switch (event.status) {
        case Status::ControlChange:
          control_change(event.channel, event.d1, event.d2);
          break;
        }
      }
    }
  }
}

void AudioCallback(float** in, float** out, size_t size)
{
  // callbacks::midi::events();
  callbacks::audio::channel_0(in[0], out[0], size);
  callbacks::audio::channel_1(in[1], out[1], size);
}

int main(void)
{
  hw.Configure();
  hw.Init();

  daisy::UartHandler uart1;
  uart1.Init();
  uart1.StartRx();

  midi_parser.Init();
  midi_out_buffer.Init();

  sfx::Chorus::Init(hw.AudioSampleRate());
  sfx::Looper::Init(hw.AudioSampleRate());

  hw.StartAudio(AudioCallback);

  bool state = false;
  hw.SetLed(false);
  while (1) {
    if (!uart1.RxActive()) {
      uart1.FlushRx();
      uart1.StartRx();
      midi_parser.cur_length = midi_parser.expected_length = 0;
    }
    while (uart1.Readable()) {
      hw.SetLed(true);
      midi_parser.Parse(uart1.PopRx());
    }
    if (CONFIRM_MIDI_RECEIVE) {
      // midi_parser.events.Write(sfx::midi::Event{ 0xB0, 0x01, 0x05, 0x7A });
      while (midi_parser.HasNext()) {
        sfx::midi::Event event = midi_parser.NextEvent();
        sfx::midi::RawEvent raw(event);
        uart1.PollTx(&raw.length, 1);
        uart1.PollTx(raw.buffer, raw.length);
      }
    }
    while (midi_out_buffer.readable()) {
      sfx::midi::RawEvent raw = midi_out_buffer.Read();
      uart1.PollTx(raw.buffer, raw.length);
    }
    daisy::System::Delay(MAIN_LOOP_FRAMETIME);
  }
}
