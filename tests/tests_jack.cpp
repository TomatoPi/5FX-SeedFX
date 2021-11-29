#include "jack/jack.hpp"
#include "alloc/heterogenous_allocator.hpp"

#include <cstdlib>
#include <cstdio>

#define TRY_JACK(code) do { \
  sfx::err_t res = code; \
  if (sfx::Success != res) \
  { \
    fprintf(stderr, "Error at %s\n\terr     : %s\n\tdetails : %s\n", #code, sfx::errname(res), sfx::errstr); \
    exit(EXIT_FAILURE); \
  } \
} while(0)

sfx::alloc::heterogenous_allocator_t* _main_allocator;

constexpr const size_t _main_mem_size = 1U << 15;
static uint8_t _main_mem[_main_mem_size];

static constexpr size_t _max_modules_count = 8;
static constexpr size_t _max_ports_count = 16;
static constexpr size_t _block_size = 128;

void print_occupancy()
{
  fprintf(stderr, "Main allocator occupancy :\n\tTotal  : %lu\n\tIn use : %lu\n\tFree   : %lu\n\tMax Contiguous : %lu\n",
    _main_mem_size,
    _main_mem_size - _main_allocator->total_available_size(),
    _main_allocator->total_available_size(),
    _main_allocator->max_available_size());
}

int main(int argc, char * const argv[])
{
  _main_allocator = new sfx::alloc::heterogenous_allocator_t(_main_mem, _main_mem_size);

  sfx::jack::engine jack;

  TRY_JACK(jack.init(_max_modules_count, _max_ports_count));
  print_occupancy();
  TRY_JACK(jack.set_blocksize(_block_size));
  print_occupancy();

  
  return 0;
}