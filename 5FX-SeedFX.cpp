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
      float in_gain = Settings.Channel0.input_gain.rms();
      float out_gain = Settings.Channel0.output_gain.rms();
      for (size_t i = 0; i < nsamples; ++i) {
        float sample = in_gain * in[i];
        sample = sfx::Chorus::Process(sample);
        sample = sfx::Delay::Process(sample);
        sample = sfx::Looper::Process(sample);
        out[i] = out_gain * sample;
      }
    }

    void channel_1(float* in, float* out, size_t nsamples)
    {
      float in_gain = Settings.Channel1.input_gain.rms();
      float out_gain = Settings.Channel1.output_gain.rms();
      for (size_t i = 0; i < nsamples; i++) {
        float sample = in_gain * in[i];
        out[i] = out_gain * sample;
      }
    }
  }

  namespace midi
  {
    void expr0(float val)
    {
      Settings.Channel0.input_gain = sfx::powlerp(val, 1.f / 8.f, -100dB, 0dB);
    }
    void expr1(float val)
    {

    }

    void expr(uint8_t channel, uint8_t val)
    {
      float fval = val / 127.f;
      switch (channel) {
      case 0:
        expr0(fval);
        break;
      case 1:
        expr1(fval);
        break;
      }
    }

    void control_change(uint8_t channel, uint8_t cc, uint8_t val)
    {
      switch (cc) {
      case 0x04:
        Pedalboard::UpdateSwitch(channel, 64 <= val);
        break;
      case 0x0B:
        expr(channel, val);
        break;
      }
    }

    void program_change(uint8_t channel, uint8_t pgm)
    {
      switch (channel) {
      case 15:
        Pedalboard::UpdateLeds();
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
        case Status::ProgramChange:
          program_change(event.channel, event.d1);
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
    if (Pedalboard::dirtyFlag) {
      Pedalboard::dirtyFlag = false;
      Pedalboard::UpdateLeds();
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
