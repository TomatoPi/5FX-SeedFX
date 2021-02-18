#include <daisy_seed.h>
#include <per/uart.h>
#include <stm32h7xx_hal_usart.h>

#include <Utility/smooth_random.h>
#include <Utility/delayline.h>

#include <initializer_list>

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

  struct Grain {
    daisysp::SmoothRandomGenerator lfo;
    size_t time;
    float read_h;

    void Init(float sr, float freq, float phase, const Granulator& g) {
      time += g.grain_length * phase;
      read_h = static_cast<float>(g.anchor);

      lfo.Init(sr);
      lfo.SetFreq(freq);
    }

    float read(const Granulator& g) {

      time = (time + 1) % g.grain_length;
      if (0 == time) {
        read_h = static_cast<float>(g.anchor);
      } else {
        read_h += 1.f;
      }
      read_h = fmod(read_h + g.depth * lfo.Process(), buffer_length);
      return window_buffer[time] * ::read(read_h);
    }
  };

  Grain ga, gb;
  size_t anchor, grain_length;
  float depth;

  void Init(float sr, float freq, float delay, float grain) {

    anchor = buffer_length - (delay * 0.001f * sr);
    grain_length = grain * 0.001f * sr;

    depth = 0.f;

    ga.Init(sr, freq, 0.f, *this);
    gb.Init(sr, freq, 0.5f, *this);
  }

  void setDepth(float d) {
    depth = d;
  }

  float read() {
    anchor = (anchor + 1) & buffer_length_mod;
    return ga.read(*this) + gb.read(*this);
  }
};

template<int Size>
struct Cloud {
  Granulator gs[Size];

  void Init(
    float sr, float grain,
    float* fs,
    float* ds) {
    for (size_t i = 0; i < Size; ++i) {
      gs[i].Init(sr, fs[i], ds[i], grain);
    }
  }

  void setDepths(float* depths) {
    for (size_t i = 0; i < Size; ++i) {
      gs[i].setDepth(depths[i]);
    }
  }

  float read() {
    float sample = 0.0f;
    for (size_t i = 0; i < Size; ++i) {
      sample += gs[i].read();
    }
    return sample / float(Size);
  }
};

Cloud<2> cloud;

void channel_0_callback(float* in, float* out, size_t nsamples) {

  for (size_t i = 0; i < nsamples; ++i) {

    float wet = cloud.read();
    float dry = in[i];
    float dw = 0.5f;
    float sample = (1.f - dw) * dry + dw * wet;

    write(dry);

    out[i] = sample;
  }
}

void channel_1_callback(float* in, float* out, size_t nsamples) {

  for (size_t i = 0; i < nsamples; i++) {
    out[i] = in[i];
  }
}

void AudioCallback(float** in, float** out, size_t size) {
  channel_0_callback(in[0], out[0], size);
  channel_1_callback(in[1], out[1], size);
}

int main(void) {

  bool state(false);

  hw.Configure();
  hw.Init();

  {
    float freqs[] = { 25.f, 10.f };
    float delays[] = { 17.f, 10.f };
    float depths[] = { 0.015f, 0.021f };
    cloud.Init(hw.AudioSampleRate(), 100.f, freqs, delays);
    cloud.setDepths(depths);
  }

  write_h = 0;

  size_t N = cloud.gs[0].grain_length;
  window_buffer = new float[N];
  for (size_t i = 0; i < N; ++i) {
    // float w = 1.f - abs((i - N_2) / N_2);
    float w = sin((M_PI * i) / (float)(N));
    window_buffer[i] = w;
  }

  hw.StartAudio(AudioCallback);

  daisy::UartHandler uart1;
  uart1.Init();
  uint8_t buff = 'a';

  while (1) {
    state = HAL_OK == uart1.PollTx(&buff, 1);
    hw.SetLed(state);
    daisy::System::Delay(1000);
  }
}
