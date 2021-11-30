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

#define CONNECT(a, b) TRY_JACK(jack.connect(a, b))

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
void dump_buffer(const sfx::jack::buffer_t* b)
{
  if (b)
    fprintf(stderr, "\t\t\t\t\tSamples : %p\n", b->samples);
}
void dump_port(const sfx::jack::port_t* p)
{
  fprintf(stderr, "\t\t\tPort : %d : %p\n", p->uid, p);
  fprintf(stderr, "\t\t\t\tBuffer : %p\n", p->buffer);
  dump_buffer(p->buffer);
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
  fprintf(stderr, "Callback for module %d\n", mod->uid);

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

  sfx::jack::module_descriptor_t mod_desc = {"ModulePouet", callback_pourrite};

  sfx::jack::port_descriptor_t phy_in_0_desc = {"PhyIn0", sfx::jack::PortIsOutput | sfx::jack::PortIsPhysical, sfx::jack::PhysicalIn0};
  sfx::jack::port_descriptor_t phy_in_1_desc = {"PhyIn1", sfx::jack::PortIsOutput | sfx::jack::PortIsPhysical, sfx::jack::PhysicalIn1};

  sfx::jack::port_descriptor_t phy_out_0_desc = {"PhyOut0", sfx::jack::PortIsInput | sfx::jack::PortIsPhysical, sfx::jack::PhysicalOut0};
  sfx::jack::port_descriptor_t phy_out_1_desc = {"PhyOut1", sfx::jack::PortIsInput | sfx::jack::PortIsPhysical, sfx::jack::PhysicalOut1};
  
  sfx::jack::port_descriptor_t in_0_desc = {"In0", sfx::jack::PortIsInput};
  sfx::jack::port_descriptor_t in_1_desc = {"In1", sfx::jack::PortIsInput};
  sfx::jack::port_descriptor_t out_0_desc = {"Out0", sfx::jack::PortIsOutput};
  sfx::jack::port_descriptor_t out_1_desc = {"Out1", sfx::jack::PortIsOutput};

  CREATE_MODULE(m0, mod_desc);
  CREATE_PORT(pA, m0, phy_out_0_desc);
  CREATE_PORT(pB, m0, phy_out_1_desc);

  CREATE_MODULE(m0b, mod_desc);
  CREATE_PORT(pC, m0b, phy_in_0_desc);

  CREATE_MODULE(m1, mod_desc);
  CREATE_PORT(pD, m1, in_0_desc);
  CREATE_PORT(pE, m1, in_1_desc);
  CREATE_PORT(pF, m1, out_0_desc);
  CREATE_PORT(pG, m1, out_1_desc);

  CREATE_MODULE(m2, mod_desc);
  CREATE_PORT(pH, m2, in_0_desc);
  CREATE_PORT(pI, m2, in_1_desc);
  CREATE_PORT(pJ, m2, out_0_desc);

  CREATE_MODULE(m3, mod_desc);
  CREATE_PORT(pK, m3, out_0_desc);

  CREATE_MODULE(m4, mod_desc);
  CREATE_PORT(pL, m4, in_0_desc);
  CREATE_PORT(pM, m4, out_0_desc);

  CREATE_MODULE(m5, mod_desc);
  CREATE_PORT(pN, m5, in_0_desc);
  CREATE_PORT(pO, m5, out_0_desc);

  dump_engine(&jack);

  TRY_JACK(jack.recompute_process_graph());
  
  dump_engine(&jack);

  CONNECT(pC, pL);
  CONNECT(pC, pD);

  CONNECT(pK, pE);

  CONNECT(pM, pH);
  CONNECT(pF, pI);
  CONNECT(pG, pA);

  CONNECT(pJ, pN);
  CONNECT(pO, pB);

  TRY_JACK(jack.recompute_process_graph());
  
  dump_engine(&jack);

  fprintf(stderr, "\nProcess frame\n\n");
  float* physical_io[4];
  for (size_t i=0; i<4; ++i)
    physical_io[i] = new float[_block_size];

  TRY_JACK(jack.process_callback(physical_io, physical_io + 2));
  dump_engine(&jack);
  
  for (size_t i=0; i<4; ++i)
    delete[] physical_io[i];


  return 0;
}