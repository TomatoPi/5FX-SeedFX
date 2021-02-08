#include <daisy_seed.h>
#include <daisysp.h>

daisy::DaisySeed hw;

void AudioCallback(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i++) {
    out[0][i] = in[0][i];
    out[1][i] = in[1][i];
  }
}

int main(void) {

  bool state(false);

  hw.Configure();
  hw.Init();
  hw.StartAudio(AudioCallback);

  while (1) {
    hw.SetLed(state);
    state = !state;
    daisy::System::Delay(1000);
  }
}
