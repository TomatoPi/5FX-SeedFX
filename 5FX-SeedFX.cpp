#include "src/Chorus.hpp"
#include "src/Utils.hpp"
#include "src/Looper.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>

daisy::DaisySeed hw;
sfx::ChorusEngine<1L << 16, 8, daisysp::SmoothRandomGenerator> chorus;
sfx::LooperEngine<1L << 1> looper;

constexpr size_t N = 1L << 16;
float DSY_SDRAM_BSS buffer[N];
size_t pos = 0;

void channel_0_callback(float* in, float* out, size_t nsamples)
{
  for (size_t i = 0; i < nsamples; ++i) {
    buffer[pos] = in[i];
    pos = (pos + 1) & (N - 1);
    out[i] = buffer[pos];
    // out[i] = chorus.Process(in[i]);
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

  {
    float freqs[] = { 25.f, 10.f };
    float delays[] = { 17.f, 10.f };
    float depths[] = { 0.015f, 0.021f };

    chorus.Init(hw.AudioSampleRate(), 100.f, freqs, delays, 2);
    chorus.SetDepths(depths);

    chorus.dry = -3db;
    chorus.wet = -3db;
    chorus.feedback = 0.f;
  }

  {
    looper.Init(hw.AudioSampleRate(), 1.f);
  }

  hw.StartAudio(AudioCallback);

  daisy::UartHandler uart1;
  uart1.Init();
  uint8_t buff = 'a';

  while (1) {
    state = 0 == uart1.PollTx(&buff, 1);
    hw.SetLed(state);
    daisy::System::Delay(1000);
  }
}
