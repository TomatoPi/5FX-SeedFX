#include "src/Global.hpp"
#include "src/Save.hpp"
#include "src/Pedalboard.hpp"

#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Delay.hpp"
#include "src/Midi.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>

using namespace sfx;

constexpr const bool DEBUG_WITH_MIDI = false;
constexpr const uint32_t MAIN_LOOP_FRAMETIME = 1;

sfx::midi::Parser<64, 16> midi_parser;
daisy::RingBuffer<sfx::midi::RawEvent, 16> midi_out_buffer;

void sfx::Pedalboard::setLed(uint8_t id, bool state)
{
  midi_out_buffer.Write(
    sfx::midi::RawEvent(3, 0xB0 | id, 0x03, state ? 0x7F : 0x00));
}

namespace callbacks
{
  namespace audio
  {
    void channel_0(float* in, float* out, size_t nsamples)
    {
      for (size_t i = 0; i < nsamples; ++i) {
        float sample = sfx::Chorus::Process(in[i]);
        sample = sfx::Delay::Process(sample);
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
    void control_change(uint8_t channel, uint8_t cc, uint8_t val)
    {
      switch (cc) {
      case 0x04:
        Pedalboard::UpdateSwitch(channel, 64 <= val);
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
  if (!DEBUG_WITH_MIDI) callbacks::midi::events();
  callbacks::audio::channel_0(in[0], out[0], size);
  callbacks::audio::channel_1(in[1], out[1], size);
}

int main(void)
{
  Hardware.Configure();
  Hardware.Init();

  daisy::UartHandler uart1;
  uart1.Init();
  uart1.StartRx();

  midi_parser.Init();
  midi_out_buffer.Init();

  Chorus::Init(Hardware.AudioSampleRate());
  Looper::Init(Hardware.AudioSampleRate());
  Delay::Init(Hardware.AudioSampleRate());

  Pedalboard::Init();

  Hardware.StartAudio(AudioCallback);

  SettingsDirtyFlag = false;

  while (1) {
    if (!uart1.RxActive()) {
      uart1.FlushRx();
      uart1.StartRx();
      midi_parser.cur_length = midi_parser.expected_length = 0;
    }
    while (uart1.Readable()) {
      midi_parser.Parse(uart1.PopRx());
    }
    if (DEBUG_WITH_MIDI) {
      while (midi_parser.HasNext()) {
        midi::Event event = midi_parser.NextEvent();
        // debug code here
      }
    }
    while (midi_out_buffer.readable()) {
      sfx::midi::RawEvent raw = midi_out_buffer.Read();
      uart1.PollTx(raw.buffer, raw.length);
    }
    if (SettingsDirtyFlag) {
      persist::SaveToQSPI();
      SettingsDirtyFlag = false;
    }
    daisy::System::Delay(MAIN_LOOP_FRAMETIME);
  }
}
