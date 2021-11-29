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

#define CREATE_MODULE(name, desc) \
  auto name = jack.create_module(&desc); \
  if (nullptr == name) \
  { \
    fprintf(stderr, "Allocation error for %s\n\terr     : %s\n\tdetails : %s\n", #name, sfx::errname((sfx::err_t)sfx::errno), sfx::errstr); \
    exit(EXIT_FAILURE); \
  }

#define CREATE_PORT(name, module, desc) \
  auto name = jack.create_port(module, &desc); \
  if (nullptr == name) \
  { \
    fprintf(stderr, "Allocation error for %s\n\terr     : %s\n\tdetails : %s\n", #name, sfx::errname((sfx::err_t)sfx::errno), sfx::errstr); \
    exit(EXIT_FAILURE); \
  }

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

void dump_connection(const sfx::jack::connection_t* c)
{
  fprintf(stderr, "\t\t\t\tConnection : %d -> %d\n", c->src, c->dst);
}
void dump_port(const sfx::jack::port_t* p)
{
  fprintf(stderr, "\t\t\tPort : %d : %p\n", p->uid, p);
  fprintf(stderr, "\t\t\t\tBuffer : %p\n", p->buffer);
  for (const sfx::jack::connection_t* con = p->connections; con != nullptr; con = con->next)
    dump_connection(con);
}
void dump_module(const sfx::jack::module_t* m)
{
  fprintf(stderr, "\t\tModule : %d : %p\n", m->uid, m);
  for (const auto* p = m->ports; p != nullptr; p = p->next)
    dump_port(p);
}

void dump_engine(sfx::jack::engine* jack)
{
  fprintf(stderr, "Jack Engine Dump\n");

  fprintf(stderr, "\tAllocated modules : %lu\n", jack->modules_allocator.used_slots_count());
  for (auto itr = jack->modules_allocator.begin(); itr != jack->modules_allocator.end(); ++itr)
    dump_module(itr.get<sfx::jack::module_t>());

  fprintf(stderr, "\tAllocated ports : %lu\n", jack->ports_allocator.used_slots_count());
  fprintf(stderr, "\tAllocated connections : %lu\n", jack->connections_allocator.used_slots_count());
  fprintf(stderr, "\tAllocated buffers : %lu\n", jack->buffers_allocator.used_slots_count());

  fprintf(stderr, "\tProcess order : ");
  for (size_t i=0; i < jack->max_modules_count && jack->process_order[i] != -1; ++i)
  {
    fprintf(stderr, "%d -> ", jack->process_order[i]);
  }
  fprintf(stderr, "-1\n");

  fprintf(stderr, "\n");
  print_occupancy();
  fprintf(stderr, "=========================\n");
}

int callback_pourrite(sfx::jack::module_t* mod)
{
  return 0;
}

int main(int argc, char * const argv[])
{
  _main_allocator = new sfx::alloc::heterogenous_allocator_t(_main_mem, _main_mem_size);

  sfx::jack::engine jack;

  TRY_JACK(jack.init(_max_modules_count, _max_ports_count));
  print_occupancy();
  TRY_JACK(jack.set_blocksize(_block_size));
  print_occupancy();

  sfx::jack::module_descriptor_t desc0 = {
    "ModulePouet", callback_pourrite
  };
  sfx::jack::port_descriptor_t pdesc00 = {"PhyIn0", sfx::jack::PORT_IS_OUTPUT | sfx::jack::PORT_IS_PHYSICAL, sfx::jack::PhysicalIn0};
  
  CREATE_MODULE(m0, desc0);
  CREATE_PORT(p0, m0, pdesc00);

  sfx::jack::module_descriptor_t desc1 = {"ModuleToto", callback_pourrite};
  sfx::jack::port_descriptor_t pdesc10 = {"In0", sfx::jack::PORT_IS_INPUT};
  sfx::jack::port_descriptor_t pdesc11 = {"Out0", sfx::jack::PORT_IS_OUTPUT};

  CREATE_MODULE(m1, desc1);
  CREATE_PORT(p1, m1, pdesc10);
  CREATE_PORT(p2, m1, pdesc11);

  sfx::jack::module_descriptor_t desc2 = {"ModuleTiti", callback_pourrite};
  sfx::jack::port_descriptor_t pdesc20 = {"PhyOut0", sfx::jack::PORT_IS_INPUT | sfx::jack::PORT_IS_PHYSICAL, sfx::jack::PhysicalOut0};
  sfx::jack::port_descriptor_t pdesc21 = {"PhyOut1", sfx::jack::PORT_IS_INPUT | sfx::jack::PORT_IS_PHYSICAL, sfx::jack::PhysicalOut1};

  CREATE_MODULE(m2, desc2);
  CREATE_PORT(p3, m2, pdesc20);
  CREATE_PORT(p4, m2, pdesc21);

  dump_engine(&jack);

  TRY_JACK(jack.recompute_process_graph());
  
  dump_engine(&jack);

  TRY_JACK(jack.connect(p0->uid, p1->uid));
  TRY_JACK(jack.connect(p2->uid, p3->uid));
  TRY_JACK(jack.recompute_process_graph());
  
  dump_engine(&jack);

  return 0;
}