#pragma once

#include "alloc.hpp"

#include <stddef.h>
#include <stdint.h>

namespace sfx
{
  namespace alloc
  {
    class pool_allocator_t : allocator_i {
    public:

      using index_t = int16_t;

      struct object_descriptor_t {
        index_t next_idx;
      };

      static constexpr size_t required_size(size_t objectsize, size_t poolsize)
      {
        return poolsize * (objectsize + sizeof(object_descriptor_t));
      }

      pool_allocator_t(uint8_t* memory, size_t objectsize, size_t poolsize) :
        descriptors{ reinterpret_cast<object_descriptor_t*>(memory) },
        objects{ reinterpret_cast<uint8_t*>(&descriptors[poolsize]) },
        objectsize{ objectsize },
        poolsize{ poolsize }
        { clear(); }

      void* alloc(size_t) override
      {
        return alloc();
      }

      void* alloc()
      {
        if (-1 == free_slots_anchor.next_idx)
          return nullptr;
        index_t idx = free_slots_anchor.next_idx;
        void* newptr = objects + (objectsize * idx);
        // move the object to occupied pool
        free_slots_anchor.next_idx = descriptors[idx].next_idx;
        descriptors[idx].next_idx = occupied_slots_anchor.next_idx;
        occupied_slots_anchor.next_idx = idx;
        // done
        return newptr;
      }

      int free(void* ptr) override
      {
        index_t idx = indexof(ptr);
        object_descriptor_t* tmp;
        // find the node pointing to target object
        for (
          tmp = &occupied_slots_anchor;
          tmp->next_idx != -1 && tmp->next_idx != idx;
          tmp = &descriptors[tmp->next_idx])
        {
        }
        if (-1 == tmp->next_idx)
          return -1;
        // move the object to free pool
        tmp->next_idx = descriptors[idx].next_idx;
        descriptors[idx].next_idx = free_slots_anchor.next_idx;
        free_slots_anchor.next_idx = idx;
        // done
        return 0;
      }

      void clear() override
      {
        free_slots_anchor.next_idx = 0;
        occupied_slots_anchor.next_idx = -1;
        for (size_t i=0 ; i<poolsize ; ++i)
          descriptors[i].next_idx = i+1;
        descriptors[poolsize-1].next_idx = -1;
      }

      index_t free_lst() const { return free_slots_anchor.next_idx; }
      index_t alloc_lst() const { return occupied_slots_anchor.next_idx; }

      size_t indexof(const object_descriptor_t* desc)
      {
        return (size_t)(desc - descriptors) / sizeof(object_descriptor_t);
      }
      size_t indexof(void* ptr)
      {
        return (size_t)((uint8_t*)ptr - objects) / objectsize;
      }
      
    private:


      object_descriptor_t*  descriptors;
      uint8_t*              objects;

      object_descriptor_t free_slots_anchor;
      object_descriptor_t occupied_slots_anchor;

      size_t objectsize;
      size_t poolsize;
    };
  }
  // namespace alloc
}
// namespace sfx
