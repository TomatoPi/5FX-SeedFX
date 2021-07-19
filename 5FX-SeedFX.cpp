#include "src/Global.hpp"
// #include "src/Pedalboard.hpp"

#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Delay.hpp"
#include "src/Midi.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>
#include <Dynamics/compressor.h>

using namespace sfx;

constexpr const bool DEBUG_WITH_MIDI = false;
constexpr const uint32_t MAIN_LOOP_FRAMETIME = 1;

sfx::midi::Parser<64, 16> midi_parser;
daisy::RingBuffer<sfx::midi::RawEvent, 16> midi_out_buffer;

Chorus::Engine::Buffer DSY_SDRAM_BSS ChorusBuffer0, ChorusBuffer1;
Chorus::Engine::Window DSY_SDRAM_BSS ChorusWindowBuffer0;
Chorus::Engine Chorus0, Chorus1;

Delay::Engine::Buffer DSY_SDRAM_BSS DelayBuffer0, DelayBuffer1;
Delay::Engine Delay0, Delay1;

sfx::Looper::Engine::Buffer DSY_SDRAM_BSS LooperBuffer0;//, LooperBuffer1;
sfx::Looper::Engine Looper0, /*Looper1,*/ * LooperX = nullptr;

size_t EditedChorusVoice = 0;

daisysp::Compressor Compressor0;

struct
{
  struct
  {
    decibel_gain input_gain = 0dB;
    decibel_gain output_gain = 0dB;
  } Channel0, Channel1;

  Chorus::Settings Chorus0, Chorus1;
  Delay::Settings Delay0, Delay1;
  Looper::Settings Looper0, Looper1;

  struct
  {
    bool bypass = true;
  } Compressor0;

} GlobalSettings;

#include "src/Save.hpp"

const struct
{
  uint8_t Delay0 = 0;
  uint8_t Chorus0 = 1;
  uint8_t Compressor0 = 2;
  
  uint8_t Delay1 = 8;
  uint8_t Chorus1 = 9;

  uint8_t Multiply = 4;
  uint8_t Oneshot = 5;
  uint8_t Overdub = 6;
  uint8_t Record = 7;

  uint8_t Mute = 13;
  uint8_t Undo = 14;
  uint8_t Redo = 15;
} Bindings;

void _BindSwitches()
{
  Pedalboard::bindSwitchAsBypass(
    Bindings.Delay0,
    []() -> bool { return GlobalSettings.Delay0.bypass; },
    [](bool b) -> void { Delay0.setBypass(b); });
  Pedalboard::bindSwitchAsBypass(
    Bindings.Chorus0,
    []() -> bool { return GlobalSettings.Chorus0.bypass; },
    [](bool b) -> void { Chorus0.setBypass(b); });
  Pedalboard::bindSwitchAsBypass(
    Bindings.Compressor0,
    []() -> bool { return GlobalSettings.Compressor0.bypass; },
    [](bool b) -> void { GlobalSettings.Compressor0.bypass = b; });

  Pedalboard::bindSwitchAsBypass(
    Bindings.Delay1,
    []() -> bool { return GlobalSettings.Delay1.bypass; },
    [](bool b) -> void { Delay1.setBypass(b); });
  Pedalboard::bindSwitchAsBypass(
    Bindings.Chorus1,
    []() -> bool { return GlobalSettings.Chorus1.bypass; },
    [](bool b) -> void { Chorus1.setBypass(b); });


  Pedalboard::bindLed(Bindings.Multiply,
    [](bool) -> bool { return Looper::Engine::State::Multiplying == LooperX->GetState(); });
  Pedalboard::bindSwitchOnFall(Bindings.Multiply, []() -> void { LooperX->HitMultiply(); });

  Pedalboard::bindLed(Bindings.Oneshot,
    [](bool) -> bool { return Looper::Engine::State::Oneshot == LooperX->GetState(); });
  Pedalboard::bindSwitchOnFall(Bindings.Oneshot, []() -> void { LooperX->HitOneshot(); });

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
      bool canrestack(LooperX->_height < LooperX->_stacksize);
      return
        (Looper::Engine::State::Playback == LooperX->GetState() && canrestack)
        || (Looper::Engine::State::Overdubed == LooperX->GetState() && canrestack)
        || (Looper::Engine::State::Idle == LooperX->GetState() && canrestack);
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

      if (!GlobalSettings.Compressor0.bypass)
        for (size_t i = 0; i < nsamples; ++i) {
          float sample = in_gain * in[i];
          sample = Compressor0.Process(sample);
          sample = Chorus0.Process(sample);
          sample = Delay0.Process(sample);
          sample = Looper0.Process(sample);
          out[i] = out_gain * sample;
        }
      else
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
        sample = Chorus1.Process(sample);
        sample = Delay1.Process(sample);
        // sample = Looper1.Process(sample);
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
      GlobalSettings.Channel1.input_gain = sfx::powlerp(val, 1.f / 8.f, -100dB, 0dB);
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
      case 0x10:
        Chorus0.setFrequency(EditedChorusVoice, mapcc(val, 0.1f, 100.f));
        break;
      case 0x11:
        Chorus0.setDelay(EditedChorusVoice, mapcc(val, 1.f, 30.f));
        break;
      case 0x12:
        Chorus0.setDepth(EditedChorusVoice, mapcc(val, 0.f, 0.1f));
        break;
      case 0x13:
        if (64 <= val)
        {
          EditedChorusVoice += 1;
          if (GlobalSettings.Chorus0.cloud_size <= EditedChorusVoice)
            EditedChorusVoice = GlobalSettings.Chorus0.cloud_size -1;
        }
        else 
        {
          if (0 < EditedChorusVoice)
            EditedChorusVoice -= 1;
        }
        break;
      case 0x14:
        size_t size = GlobalSettings.Chorus0.cloud_size;
        if (64 <= val)
        {
          size += 1;
          if (Chorus::CloudMaxSize <= size)
            size = Chorus::CloudMaxSize -1;
        }
        else 
        {
          if (0 < size)
            size -= 1;
        }
        Chorus0.setCloudSize(size);
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

  // persist::LoadFromQSPI();

  daisy::UartHandler uart1;
  uart1.Init();
  uart1.StartRx();

  midi_parser.Init();
  midi_out_buffer.Init();

  Chorus0.Init(Hardware.AudioSampleRate(), &ChorusBuffer0, ChorusWindowBuffer0, &GlobalSettings.Chorus0);
  Delay0.Init(Hardware.AudioSampleRate(), &DelayBuffer0, &GlobalSettings.Delay0);
  Looper0.Init(Hardware.AudioSampleRate(), &LooperBuffer0, &GlobalSettings.Looper0);
  Compressor0.Init(Hardware.AudioSampleRate());

  Compressor0.SetAttack(0.1);
  Compressor0.SetMakeup(30);
  Compressor0.SetRatio(3);
  Compressor0.SetRelease(1);
  Compressor0.SetThreshold(-60);

  Chorus1.Init(Hardware.AudioSampleRate(), &ChorusBuffer1, ChorusWindowBuffer0, &GlobalSettings.Chorus1);
  Delay1.Init(Hardware.AudioSampleRate(), &DelayBuffer1, &GlobalSettings.Delay1);
  //Looper1.Init(Hardware.AudioSampleRate(), &LooperBuffer1, &GlobalSettings.Looper1);

  // Looper0._link = &Looper1;
  // Looper1._link = &Looper0;
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
