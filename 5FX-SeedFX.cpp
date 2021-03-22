#include "src/Global.hpp"
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

Chorus::Engine::Buffer DSY_SDRAM_BSS ChorusBuffer0;
Chorus::Engine::Window DSY_SDRAM_BSS ChorusWindowBuffer0;
Chorus::Engine Chorus0;

Delay::Engine::Buffer DSY_SDRAM_BSS DelayBuffer0;
Delay::Engine Delay0;

sfx::Looper::Engine::Buffer DSY_SDRAM_BSS LooperBuffer0, LooperBuffer1;
sfx::Looper::Engine Looper0, Looper1, * LooperX = nullptr;

struct
{
  struct
  {
    decibel_gain input_gain = 0dB;
    decibel_gain output_gain = 0dB;
  } Channel0, Channel1;

  Chorus::Settings Chorus0;
  Delay::Settings Delay0;
  Looper::Settings Looper0, Looper1;
} GlobalSettings;

#include "src/Save.hpp"

const struct
{
  uint8_t Delay = 0;
  uint8_t Chorus = 1;

  uint8_t SelLooper0 = 4;
  uint8_t SelLooper1 = 12;

  uint8_t Overdub = 6;
  uint8_t Record = 7;

  uint8_t Mute = 13;
  uint8_t Undo = 14;
  uint8_t Redo = 15;
} Bindings;

void _BindSwitches()
{

  Pedalboard::bindSwitchAsBypass(
    Bindings.Delay,
    []() -> bool { return GlobalSettings.Delay0.bypass; },
    [](bool b) -> void { Delay0.setBypass(b); });
  Pedalboard::bindSwitchAsBypass(
    Bindings.Chorus,
    []() -> bool { return GlobalSettings.Chorus0.bypass; },
    [](bool b) -> void { Chorus0.setBypass(b); });

  Pedalboard::bindLed(Bindings.Record,
    [](bool) -> bool { return Looper::Engine::State::Recording == LooperX->GetState(); });
  Pedalboard::bindSwitchOnFall(Bindings.Record, []() -> void { LooperX->HitRecord(); });

  Pedalboard::bindLed(Bindings.Overdub,
    [](bool) -> bool { return Looper::Engine::State::Overdubing == LooperX->GetState(); });
  Pedalboard::bindSwitchOnFall(Bindings.Overdub, []() -> void { LooperX->HitOverdub(); });

  Pedalboard::bindLed(Bindings.Undo,
    [](bool) -> bool
    {
      return Looper::Engine::State::Playback == LooperX->GetState()
        || Looper::Engine::State::Overdubed == LooperX->GetState();
    });
  Pedalboard::bindSwitchOnFall(Bindings.Undo, []() -> void { LooperX->HitUndo(); });

  Pedalboard::bindLed(Bindings.Redo,
    [](bool) -> bool
    {
      return
        (Looper::Engine::State::Playback == LooperX->GetState() && 0 < LooperX->_stacksize)
        || (Looper::Engine::State::Overdubed == LooperX->GetState() && LooperX->_height < LooperX->_stacksize)
        || (Looper::Engine::State::Idle == LooperX->GetState() && 0 < LooperX->_rec_length);
    });
  Pedalboard::bindSwitchOnFall(Bindings.Redo, []() -> void { LooperX->HitRedo(); });

  Pedalboard::bindLed(Bindings.Mute,
    [](bool) ->bool { return Looper::Engine::State::Muted == LooperX->GetState(); });
  Pedalboard::bindSwitchOnFall(Bindings.Mute, []() -> void { LooperX->HitMute(); });
}

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
      float in_gain = GlobalSettings.Channel0.input_gain.rms();
      float out_gain = GlobalSettings.Channel0.output_gain.rms();
      for (size_t i = 0; i < nsamples; ++i) {
        float sample = in_gain * in[i];
        sample = Chorus0.Process(sample);
        sample = Delay0.Process(sample);
        sample = Looper0.Process(sample);
        out[i] = out_gain * sample;
      }
    }

    void channel_1(float* in, float* out, size_t nsamples)
    {
      float in_gain = GlobalSettings.Channel1.input_gain.rms();
      float out_gain = GlobalSettings.Channel1.output_gain.rms();
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
      GlobalSettings.Channel0.input_gain = sfx::powlerp(val, 1.f / 8.f, -100dB, 0dB);
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

  Chorus0.Init(Hardware.AudioSampleRate(), &ChorusBuffer0, ChorusWindowBuffer0, &GlobalSettings.Chorus0);
  Delay0.Init(Hardware.AudioSampleRate(), &DelayBuffer0, &GlobalSettings.Delay0);
  Looper0.Init(Hardware.AudioSampleRate(), &LooperBuffer0, &GlobalSettings.Looper0);

  Looper1.Init(Hardware.AudioSampleRate(), &LooperBuffer1, &GlobalSettings.Looper1);

  LooperX = &Looper0;

  _BindSwitches();
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
