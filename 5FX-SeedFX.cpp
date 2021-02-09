#include <daisy_seed.h>

#include <Utility/smooth_random.h>
#include <Utility/delayline.h>

daisy::DaisySeed hw;

float* window_buffer;

size_t write_h;
constexpr const size_t buffer_length = 1 << 16;
constexpr const size_t buffer_length_mod = buffer_length - 1;
float buffer[buffer_length];

float read(float t) {
  int ti = static_cast<int>(t);
  float tf = t - ti;
  float a = buffer[ti];
  float b = buffer[(ti + 1) & buffer_length_mod];
  return (1.f - tf) * a + tf * b;
}

void write(float x) {
  write_h = (write_h + 1) & buffer_length_mod;
  buffer[write_h] = x;
}

struct Granulator {
  daisysp::SmoothRandomGenerator lfo;
  size_t anchor, grain_length, time;
  float read_h;
  float depth;

  void Init(float sr, float freq, float delay, float grain, float phase = 0.f) {

    anchor = buffer_length - (delay * 0.001f * sr);
    grain_length = grain * 0.001f * sr;
    time += grain_length * phase;
    read_h = static_cast<float>(anchor);

    depth = 0.f;

    lfo.Init(sr);
    lfo.SetFreq(freq);
  }

  void setDepth(float d) {
    depth = d;
  }

  float read() {

    time = (time + 1) % grain_length;
    if (0 == time) {
      read_h = static_cast<float>(anchor);
    } else {
      read_h += 1.f;
    }
    read_h = fmod(read_h + depth * lfo.Process(), buffer_length);
    anchor = (anchor + 1) & buffer_length_mod;
    return window_buffer[time] * ::read(read_h);
  }
};

Granulator ga, gb;

void AudioCallback(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i++) {

    float wet = ga.read() + gb.read();
    float dry = in[0][i];
    float dw = 0.6f;
    float sample = (1.f - dw) * dry + dw * wet;

    write(dry);

    out[0][i] = sample;
    out[1][i] = in[1][i];
  }
}

int main(void) {

  bool state(false);

  hw.Configure();
  hw.Init();

  ga.Init(hw.AudioSampleRate(), 500.f, 17.f, 100.f, 0.f);
  gb.Init(hw.AudioSampleRate(), 500.f, 17.f, 100.f, 0.5f);

  ga.setDepth(0.02f);
  gb.setDepth(0.02f);

  write_h = 0;

  window_buffer = new float[ga.grain_length];
  float N_2 = ga.grain_length / 2.f;
  for (size_t i = 0; i < ga.grain_length; ++i) {
    // float w = 1.f - abs((i - N_2) / N_2);
    float w = sin((M_PI * i) / (float)(ga.grain_length));
    window_buffer[i] = w;
  }

  hw.StartAudio(AudioCallback);

  while (1) {
    hw.SetLed(state);
    state = !state;
    daisy::System::Delay(1000);
  }
}
