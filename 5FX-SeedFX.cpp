#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"
#include "src/Midi.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>
#include <Noise/clockednoise.h>

constexpr const bool DEBUG_WITH_MIDI = true;
constexpr const uint32_t MAIN_LOOP_FRAMETIME = 1;

daisy::DaisySeed hw;
sfx::midi::Parser<64, 16> midi_parser;
daisy::RingBuffer<sfx::midi::RawEvent, 16> midi_out_buffer;

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
  if (!DEBUG_WITH_MIDI) callbacks::midi::events();
  callbacks::audio::channel_0(in[0], out[0], size);
  callbacks::audio::channel_1(in[1], out[1], size);
}

constexpr const uint32_t QSPI_BLOCK_SIZE = 4096;

constexpr const uint32_t SaveSectionSize = QSPI_BLOCK_SIZE;
constexpr const uint32_t SaveSectionBegin = 0x9000'0000;
constexpr const uint32_t SaveSectionEnd = SaveSectionBegin + SaveSectionSize;
uint8_t DSY_QSPI_BSS SaveSectionBlock[SaveSectionSize];

uint8_t qspi_test_values[128] = { 0 };

void write_to_qspi()
{
  dsy_qspi_deinit();
  hw.qspi_handle.mode = DSY_QSPI_MODE_INDIRECT_POLLING;
  dsy_qspi_init(&hw.qspi_handle);

  dsy_qspi_erase(SaveSectionBegin, SaveSectionEnd);
  dsy_qspi_write(SaveSectionBegin, 128, qspi_test_values);

  dsy_qspi_deinit();
}
void read_from_qspi()
{
  dsy_qspi_deinit();
  hw.qspi_handle.mode = DSY_QSPI_MODE_DSY_MEMORY_MAPPED;
  dsy_qspi_init(&hw.qspi_handle);

  memcpy(qspi_test_values, SaveSectionBlock, 128);

  dsy_qspi_deinit();
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
        sfx::midi::Event event = midi_parser.NextEvent();
        if (event.status == 0x80) {
          qspi_test_values[event.d1] = event.d2;
        } else if (event.status == 0x90) {
          uart1.PollTx(qspi_test_values + event.d1, 1);
        } else if (event.status == 0xA0) {
          write_to_qspi();
        } else if (event.status == 0xB0) {
          read_from_qspi();
        }
      }
    }
    while (midi_out_buffer.readable()) {
      sfx::midi::RawEvent raw = midi_out_buffer.Read();
      uart1.PollTx(raw.buffer, raw.length);
    }
    daisy::System::Delay(MAIN_LOOP_FRAMETIME);
  }
}
