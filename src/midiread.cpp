#include <jack/jack.h>
#include <jack/midiport.h>
#include <queue>
#include <array>
#include <cstring>
#include <iostream>
#include <unistd.h>

constexpr const size_t Msglen = 8;
std::queue<std::array<uint8_t, Msglen>> sendingqueue;
jack_port_t* outport=nullptr;

int callback(jack_nframes_t nframes, void* args)
{
  void* buffer = jack_port_get_buffer(outport, nframes);

  jack_midi_event_t event;
  for (jack_nframes_t i = 0 ; i < jack_midi_get_event_count(buffer) ; ++i)
  {
    if (jack_midi_event_get(&event, buffer, i))
      continue;

    std::array<uint8_t, Msglen> data;
    memcpy(data.data(), event.buffer, Msglen);
    sendingqueue.push(data); 
  }
  return 0;
}

int main(int argc, const char* argv[])
{
  jack_status_t status;
  jack_client_t* client = jack_client_open("MidiSend", JackNullOption, &status);
  if (!client)
    return -1;
  
  outport = jack_port_register(client, "out", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
  if (!outport)
    return -2;

  if (jack_set_process_callback(client, callback, nullptr))
    return -3;

  if (jack_activate(client))
    return -4;

  while (1)
  {
    if (sendingqueue.empty())
    {
      sleep(1);
      continue;
    }
    auto event = sendingqueue.front();
    std::cout << '"';
    for (auto& c : event) std::cout << c;
    std::cout << '"' << '\n';
    sendingqueue.pop();
  }

  jack_deactivate(client);
  jack_client_close(client);
  
  return 0;
}