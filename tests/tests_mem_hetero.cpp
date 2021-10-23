#include "../src/alloc/heterogenous_allocator.hpp"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR(fmt, ...) if(1) { fprintf(stderr, fmt, ##__VA_ARGS__); exit(EXIT_FAILURE); }

const size_t memsize = 1024;
uint8_t memory[memsize] = {0};

size_t memoffset(const void* addr)
{
  return (size_t)((uint8_t*)addr - memory);
}

void dump_descriptor(const sfx::alloc::heterogenous_allocator_t::memblock_desc_t* desc)
{
  printf("\t%lu : %s : blocksize : %4ld : next : %p\n",
    memoffset(desc), (desc->is_free() ? "Free" : "Used"), desc->blocksize(), desc->next); 
  printf("\t\tMemory block : %p : %lu\n", desc->memblock(), memoffset(desc->memblock()));
  printf("\t\tNext contiguous block addr : %lu\n",
    memoffset(desc->next_contiguous_block()));
}

void dump_memory(const sfx::alloc::heterogenous_allocator_t* allocator)
{
  const auto desc = reinterpret_cast<const sfx::alloc::heterogenous_allocator_t::memblock_desc_t*>(memory);
  printf("\n=================\n");
  printf("Memory Dump :\n\tMemory Pool Size : %lu\n\tDescriptor Size : %lu\n", memsize, sizeof(*desc));
  printf("-----------------\n");
  printf("Free descriptors :\n");
  for (const auto* tmp = allocator->freelst() ; tmp != nullptr ; tmp = tmp->next)
    dump_descriptor(tmp);
  printf("-----------------\n");
  printf("Occupied descriptors :\n");
  for (const auto* tmp = allocator->alloclst() ; tmp != nullptr ; tmp = tmp->next)
    dump_descriptor(tmp);
  printf("-----------------\n");
  printf("Raw Memory Dump :\n");
  for (const sfx::alloc::heterogenous_allocator_t::memblock_desc_t* tmp = desc;
    (uint8_t*)tmp < memory + memsize;
    tmp = tmp->next_contiguous_block())
  {
    dump_descriptor(tmp);
  }
  printf("=================\n\n");
}

int main(int argc, const char* argv[])
{

  sfx::alloc::heterogenous_allocator_t allocator{ memory, memsize };
  dump_memory(&allocator);

  void* ptr = allocator.alloc(16);
  printf("Allocated address : %p : %lu\n", ptr, memoffset(ptr));
  dump_memory(&allocator);

  void* ptr1 = allocator.alloc(32);
  printf("Allocated address : %p : %lu\n", ptr1, memoffset(ptr1));
  dump_memory(&allocator);

  void* ptr2 = allocator.alloc(48);
  printf("Allocated address : %p : %lu\n", ptr2, memoffset(ptr2));
  dump_memory(&allocator);

  if (allocator.free(ptr) < 0)
    ERROR("Free error\n");
  printf("Fried address : %p : %lu\n", ptr, memoffset(ptr));
  dump_memory(&allocator);


  if (allocator.free(ptr2) < 0)
    ERROR("Free error\n");
  printf("Fried address : %p : %lu\n", ptr2, memoffset(ptr2));
  dump_memory(&allocator);


  allocator.optimize_memory();
  printf("Optimized Memory");
  dump_memory(&allocator);


  ptr = allocator.alloc(16);
  printf("Allocated address : %p : %lu\n", ptr, memoffset(ptr));
  dump_memory(&allocator);

  ptr2 = allocator.alloc(16);
  printf("Allocated address : %p : %lu\n", ptr2, memoffset(ptr2));
  dump_memory(&allocator);


  if (allocator.free(ptr2) < 0)
    ERROR("Free error\n");
  printf("Fried address : %p : %lu\n", ptr2, memoffset(ptr2));
  dump_memory(&allocator);

  if (allocator.free(ptr1) < 0)
    ERROR("Free error\n");
  printf("Fried address : %p : %lu\n", ptr1, memoffset(ptr1));
  dump_memory(&allocator);

  if (allocator.free(ptr) < 0)
    ERROR("Free error\n");
  printf("Fried address : %p : %lu\n", ptr, memoffset(ptr));
  dump_memory(&allocator);


  allocator.optimize_memory();
  printf("Optimized Memory");
  dump_memory(&allocator);

  return 0;
}