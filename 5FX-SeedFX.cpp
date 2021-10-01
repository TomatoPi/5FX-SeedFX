#include "src/Global.hpp"
// #include "src/Pedalboard.hpp"

#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Delay.hpp"
#include "src/Serial.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>
#include <Dynamics/compressor.h>


daisy::UartHandler uart1;

static serial::messages::Scan::DeviceDescription _SeedFXDeviceDescriptor =
{
  {'S', 'e', 'e', 'd', 'F', 'X'},
  0xA0,
  1,

  0
};
static uint8_t last_scan_uid = 0xE1;

serial::messages::Scan GenerateScanMessage() {
  serial::messages::Scan msg;
  msg.device = _SeedFXDeviceDescriptor;
  msg.scan_uid = ++last_scan_uid;
  return msg;
}

using namespace sfx;

constexpr const bool DEBUG_WITH_MIDI = false;
constexpr const uint32_t MAIN_LOOP_FRAMETIME = 1;

serial::SerialParser serial_in;
daisy::RingBuffer<serial::Packet, 32> serial_in_buffer;
daisy::RingBuffer<serial::Packet, 32> serial_out_buffer;

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
  // serial::messages::SetLed msg;
  // msg.index = id;
  // msg.state = state;
  // serial_out_buffer.Write(serial::Serialize(msg));
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

  // namespace midi
  // {
  //   void expr0(float val)
  //   {
  //     GlobalSettings.Channel0.input_gain = sfx::powlerp(val, 1.f / 8.f, -100dB, 0dB);
  //   }
  //   void expr1(float val)
  //   {
  //     GlobalSettings.Channel1.input_gain = sfx::powlerp(val, 1.f / 8.f, -100dB, 0dB);
  //   }

  //   void expr(uint8_t channel, uint8_t val)
  //   {
  //     float fval = val / 127.f;
  //     switch (channel) {
  //     case 0:
  //       expr0(fval);
  //       break;
  //     case 1:
  //       expr1(fval);
  //       break;
  //     }
  //   }

  //   void control_change(uint8_t channel, uint8_t cc, uint8_t val)
  //   {
  //     switch (cc) {
  //     case 0x04:
  //       Pedalboard::UpdateSwitch(channel, 64 <= val);
  //       break;
  //     case 0x0B:
  //       expr(channel, val);
  //       break;
  //     case 0x10:
  //       Chorus0.setFrequency(EditedChorusVoice, mapcc(val, 0.1f, 100.f));
  //       break;
  //     case 0x11:
  //       Chorus0.setDelay(EditedChorusVoice, mapcc(val, 1.f, 30.f));
  //       break;
  //     case 0x12:
  //       Chorus0.setDepth(EditedChorusVoice, mapcc(val, 0.f, 0.1f));
  //       break;
  //     case 0x13:
  //       if (64 <= val)
  //       {
  //         EditedChorusVoice += 1;
  //         if (GlobalSettings.Chorus0.cloud_size <= EditedChorusVoice)
  //           EditedChorusVoice = GlobalSettings.Chorus0.cloud_size -1;
  //       }
  //       else 
  //       {
  //         if (0 < EditedChorusVoice)
  //           EditedChorusVoice -= 1;
  //       }
  //       break;
  //     case 0x14:
  //       size_t size = GlobalSettings.Chorus0.cloud_size;
  //       if (64 <= val)
  //       {
  //         size += 1;
  //         if (Chorus::CloudMaxSize <= size)
  //           size = Chorus::CloudMaxSize -1;
  //       }
  //       else 
  //       {
  //         if (0 < size)
  //           size -= 1;
  //       }
  //       Chorus0.setCloudSize(size);
  //       break;
  //     }
  //   }

  //   void program_change(uint8_t channel, uint8_t pgm)
  //   {
  //     switch (channel) {
  //     case 15:
  //       Pedalboard::UpdateLeds();
  //       break;
  //     }
  //   }

  //   void events()
  //   {
  //     while (serial_in_buffer.readable())
  //     {
  //       serial::Packet packet = serial_in_buffer.Read();
  //       switch (packet.header[serial::Packet::Header::Type])
  //       {
  //         default :
  //           // Err
  //           break;
  //       }
  //     }
  //   }
  // } // namespace midi

  namespace serial
  {
    void process_input_message(const ::serial::Packet& packet)
    {
      switch (packet.header[::serial::Packet::Header::Type])
      {
        case ::serial::messages::Types::Scan :
        {
          auto scan = packet.read<::serial::messages::Scan>();
          if (scan.scan_uid != last_scan_uid)
          {
            last_scan_uid = scan.scan_uid;
            
            ::serial::messages::Scan msg;
            msg.device = _SeedFXDeviceDescriptor;
            msg.scan_uid = scan.scan_uid;

            serial_out_buffer.Write(::serial::Serialize(msg));
            // TODO : do things with the new peripheral
          }
        } break;

        case ::serial::messages::Types::QueryDevice :
        {
          auto query = packet.read<::serial::messages::QueryDevice>();
          if (_SeedFXDeviceDescriptor.uuid == query.uuid)
          {
            for (size_t i=0 ; i < sfx::_descriptors_cout ; ++i)
            {
              serial_out_buffer.Write(::serial::Serialize(_descriptors[i]));
            }
          }
        } break;

        default :
          break;
      }
    }
  } // namespace serial

} // namespace callbacks

void AudioCallback(float** in, float** out, size_t size)
{
  callbacks::audio::channel_0(in[0], out[0], size);
  callbacks::audio::channel_1(in[1], out[1], size);
}

int main(void)
{

  Hardware.Configure();
  Hardware.Init();

  // persist::LoadFromQSPI();
  uart1.Init();
  uart1.StartRx();

  serial_in_buffer.Init();
  serial_out_buffer.Init();

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

  _SeedFXDeviceDescriptor.params_count = _descriptors_cout;
  serial_out_buffer.Write(serial::Serialize(GenerateScanMessage()));

  SettingsDirtyFlag = false;

  while (1) {
    if (!uart1.RxActive()) {
      uart1.FlushRx();
      uart1.StartRx();
      serial_in.error(0);
    }
    while (uart1.Readable()) {
      uint8_t byte = uart1.PopRx();
      serial::ParsingResult result = serial_in.parse(byte);

      switch (result.status)
      {
      case serial::ParsingResult::Status::Running:
        break;
      case serial::ParsingResult::Status::Started:
        // drop = false;
        break;
      case serial::ParsingResult::Status::Finished:
        callbacks::serial::process_input_message(result.packet);
        break;
      case serial::ParsingResult::Status::EndOfStream:
        break;
      default:
        serial_in.error(0);
        break;
      }
    }
    if (Pedalboard::dirtyFlag) {
      Pedalboard::dirtyFlag = false;
      Pedalboard::UpdateLeds();
    }
    while (serial_out_buffer.readable()) {
      serial::Packet packet = serial_out_buffer.Read();
      uart1.PollTx(const_cast<uint8_t*>(packet.serialize()), packet.size());daisy::System::Delay(50);
    }
    if (SettingsDirtyFlag) {
      persist::SaveToQSPI();
      SettingsDirtyFlag = false;
    }
    daisy::System::Delay(MAIN_LOOP_FRAMETIME);
  }
}
