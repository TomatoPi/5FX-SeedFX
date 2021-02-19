#include "src/Utils.hpp"
#include "src/Chorus.hpp"
#include "src/Looper.hpp"

#include <daisy_seed.h>
#include <per/uart.h>

#include <Utility/smooth_random.h>

daisy::DaisySeed hw;

sfx::LooperEngine<1L << 1> looper;

void channel_0_callback(float* in, float* out, size_t nsamples)
{
  for (size_t i = 0; i < nsamples; ++i) {
    // buffer.Write(in[i]);
    // out[i] = buffer.Read(pos);
    // pos = (pos + 1) & (N - 1);
    out[i] = sfx::Chorus::Process(in[i]);
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

  sfx::Chorus::Init(hw.AudioSampleRate());

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
