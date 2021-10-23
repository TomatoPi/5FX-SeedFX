#include "src/jack/Graph.hpp"

#include "daisy_seed.h"

#include <stdio.h>
#include <string.h>

static daisy::DaisySeed hw;

uint8_t sumbuff[512] = {0} ;

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
    sfx::jack::port_descriptor_t port_descriptors[] = {
      { "Out_Left", true, true },
      { "Out_Right", true, true },
      { "In_Left", true, true },
      { "In_Right", true, true },
    };
    sfx::jack::input_port_t input_ports[] = {
      { &port_descriptors[0], nullptr },
      { &port_descriptors[1], nullptr },
    };
    sfx::jack::output_port_t output_ports[] = {
      { &port_descriptors[2], nullptr },
      { &port_descriptors[3], nullptr },
    };

    sfx::jack::module_descriptor_t module_descriptor = {
      "System",
      nullptr,
      0
    };
    sfx::jack::module_t module = {
      &module_descriptor,

      nullptr,

      input_ports,
      output_ports,
      nullptr,

      2, 2, 0
    };
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
  for (size_t i=0 ; i<2 ; ++i)
  {
    builtins::system::input_ports[i].buffer = out[i];
    builtins::system::output_ports[i].buffer = const_cast<float*>(in[i]);
  }
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