#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>

#include "../src/alloc/static_allocator.hpp"

#define ERROR(fmt, ...) if(1) { fprintf(stderr, fmt, ##__VA_ARGS__); exit(EXIT_FAILURE); }

const size_t memsize = 1 << 14;
uint8_t memory[memsize] = {0};
sfx::alloc::heterogenous_mempool_adaptator_t main_memory{memory, memsize};
 
size_t memoffset(const void* addr)
{
  return (size_t)((uint8_t*)addr - memory);
}

void dump_descriptor(const sfx::alloc::memblock_desc_t* desc)
{
  printf("\t%lu : %s : blocksize : %4d : next : %p\n",
    memoffset(desc), (desc->is_free() ? "Free" : "Used"), desc->blocksize(), desc->next); 
  printf("\t\tMemory block : %p : %lu\n", desc->memblock(), memoffset(desc->memblock()));
  printf("\t\tNext contiguous block addr : %lu\n",
    memoffset(desc->next_contiguous_block()));
}

void dump_memory()
{
  printf("\n=================\n");
  printf("Memory Dump :\n\tMemory Pool Size : %lu\n\tDescriptor Size : %lu\n", memsize, sizeof(sfx::alloc::memblock_desc_t));
  printf("-----------------\n");
  printf("Free descriptors :\n");
  for (const auto* tmp = main_memory.freelst() ; tmp != nullptr ; tmp = tmp->next)
    dump_descriptor(tmp);
  printf("-----------------\n");
  printf("Occupied descriptors :\n");
  for (const auto* tmp = main_memory.alloclst() ; tmp != nullptr ; tmp = tmp->next)
    dump_descriptor(tmp);
  printf("=================\n\n");
}

int main()
{
  main_memory.clear();

  std::vector<int, sfx::alloc::static_allocator<int, &main_memory>> v;
  v.push_back(42);

  dump_memory();

  for (const auto& x : v)
    printf("%d ", x);
  printf("\n");

  for (size_t i=0 ; i<100 ; ++i)
  {
    printf("%d\n", i);
    v.push_back(i);
    dump_memory();
  }
  
  for (const auto& x : v)
    printf("%d ", x);
  printf("\n");

  return 0;
}
