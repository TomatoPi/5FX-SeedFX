#include <jack/jack.h>
#include <iostream>
#include <unistd.h>

int callback(jack_nframes_t nframes, void* args)
{
  return 0;
}

int main(int argc, char * const argv[])
{
  jack_status_t status;
  jack_client_t* client = jack_client_open("PortTest", JackNullOption, &status);
  if (!client)
    return 1;

  jack_port_t* port = jack_port_register(client, "test", "Coucou", JackPortIsInput, 16);
  if (!port)
    return 2;

  if (jack_set_process_callback(client, callback, nullptr))
    return 3;

  if (jack_activate(client))
    return 4;

  usleep(10'000'000);

  jack_deactivate(client);
  jack_client_close(client);

  return 0;
}