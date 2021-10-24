#include "../src/alloc/object_pool_allocator.hpp"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR(fmt, ...) if(1) { fprintf(stderr, fmt, ##__VA_ARGS__); exit(EXIT_FAILURE); }

const size_t objectsize = sizeof(float);
const size_t poolsize = 16;
const size_t memsize = sfx::alloc::pool_allocator_t::required_size(objectsize, poolsize);

uint8_t memory[memsize] = {0};

void dump_memory(const sfx::alloc::pool_allocator_t* alloc)
{
  printf("\n===================\n");
  printf("Memory dump :\n\tObjsize : %lu\n\tPoolsize : %lu\n\tMemorySize : %lu\n", objectsize, poolsize, memsize);

  printf("Free slots :\n\t");
  const int16_t* indexes = reinterpret_cast<int16_t*>(memory);
  for (int i=alloc->free_lst() ; i != -1 ; i = indexes[i])
    printf(" -> %d", i);
  printf(" -> -1\n");

  printf("Occupied slots :\n\t");
  for (int i=alloc->alloc_lst() ; i != -1 ; i = indexes[i])
    printf(" -> %d", i);
  printf(" -> -1\n");

  printf("Raw dump :\n\t");
  for (size_t i=0 ; i < poolsize ; ++i)
    printf("%d ", indexes[i]);
  printf("\n");
  printf("\n===================\n");
}

int main(int argc, const char* argv[])
{
  srand(0);
  
  sfx::alloc::pool_allocator_t allocator{ memory, objectsize, poolsize };
  dump_memory(&allocator);

  void* ptr = allocator.alloc();
  printf("Allocated : %p : %lu\n", ptr, allocator.indexof(ptr));
  dump_memory(&allocator);

  void* ptrs[8];
  for (size_t i=0 ; i<8 ; ++i)
    ptrs[i] = allocator.alloc();
  dump_memory(&allocator);

  for (size_t i=0 ; i<4 ; ++i)
    allocator.free(ptrs[rand()%8]);
  dump_memory(&allocator);

  return 0;
}