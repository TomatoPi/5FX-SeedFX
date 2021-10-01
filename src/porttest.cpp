#include <jack/jack.h>
#include <jack/midiport.h>
#include <queue>
#include <array>
#include <cstring>
#include <iostream>

std::queue<std::array<uint8_t, 3>> sendingqueue;
jack_port_t* outport=nullptr;

int callback(jack_nframes_t nframes, void* args)
{
  // void* buffer = jack_port_get_buffer(outport, nframes);
  // jack_midi_clear_buffer(buffer);
  // while (!sendingqueue.empty())
  // {
  //   jack_midi_data_t* data = jack_midi_event_reserve(buffer, 0, 3);
  //   auto event = sendingqueue.front();
  //   memcpy(data, event.data(), 3);
  //   sendingqueue.pop();
  // }
  return 0;
}

int main(int argc, const char* argv[])
{
  jack_status_t status;
  jack_client_t* client = jack_client_open("MidiSend", JackNullOption, &status);
  if (!client)
    return -1;
  
  outport = jack_port_register(client, "output", "SFX_IPC", JackPortIsOutput, 16);
  if (!outport)
    return -2;

  if (jack_set_process_callback(client, callback, nullptr))
    return -3;

  if (jack_activate(client))
    return -4;

  while (1)
  {
    std::array<uint8_t, 3> tmp;
    for (int i=0; i<3; ++i)
      scanf(" %x", &tmp[i]);

    // std::cout << "Dump [";
    // for (auto x : tmp) 
    //   std::cout << (int)x << " ";
    // std::cout << '\b' << ']';

    sendingqueue.push(tmp);
  }

  jack_deactivate(client);
  jack_client_close(client);
  
  return 0;
}