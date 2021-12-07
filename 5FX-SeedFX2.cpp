#include "src/jack/jack.hpp"
#include "src/alloc/heterogenous_allocator.hpp"

#include "daisy_seed.h"

#include <stdio.h>
#include <string.h>

static daisy::DaisySeed hw;
static sfx::jack::engine_t jack;

uint8_t sumbuff[512] = {0} ;

constexpr const size_t _main_mem_size = 1U << 15;
static uint8_t _main_mem[_main_mem_size];
sfx::alloc::heterogenous_allocator_t* _main_allocator;


namespace builtins
{
  namespace system
  {
    /* 
    * WARNING :
    *   System's input and output are reversed, from software perspective
    *     physical_in is an output port (a port which from we read)
    *     and physical_out is an input (a port which we write on)
    */
  }
}
// namespace builtins

void UsbCallback(uint8_t* buf, uint32_t* len)
{
  for(size_t i = 0; i < *len; i++)
  {
    sumbuff[i] = buf[i];
  }
  sumbuff[*len] = '\0';
}

void AudioCallback(daisy::AudioHandle::InputBuffer  in,
                   daisy::AudioHandle::OutputBuffer out,
                   size_t                           size)
{
  if (size != jack.blocksize)
    jack.set_blocksize(size);
  jack.process_callback(in, out);
}


int main(void)
{
  hw.Configure();
  hw.Init();
  hw.usb_handle.Init(daisy::UsbHandle::FS_INTERNAL);
  int  tick_cnt = 0;
  bool ledstate = false;
  char buff[1024];
  sprintf(buff, "Tick:\t%d\n\"%s\"\n", tick_cnt, sumbuff);
  hw.usb_handle.TransmitInternal((uint8_t*)buff, strlen(buff));
  daisy::System::Delay(500);
  hw.usb_handle.SetReceiveCallback(UsbCallback, daisy::UsbHandle::FS_INTERNAL);

  sfx::alloc::heterogenous_allocator_t __main_allocator(_main_mem, _main_mem_size);
  _main_allocator = &__main_allocator;

  jack.init(8, 16);
  jack.set_blocksize(hw.AudioBlockSize());
  jack.recompute_process_graph();

  hw.StartAudio(AudioCallback);
  while(1)
  {
    daisy::System::Delay(500);
    sprintf(buff, "Tick:\t%d\n\"%s\"\n", tick_cnt, sumbuff);
    hw.usb_handle.TransmitInternal((uint8_t*)buff, strlen(buff));
    tick_cnt = (tick_cnt + 1) % 100;
    hw.SetLed(ledstate);
    ledstate = !ledstate;
  }
}