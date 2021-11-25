#pragma once

#include "alloc.hpp"

#include <stddef.h>
#include <stdint.h>

namespace sfx
{
  namespace alloc
  {
    template <typename index_t>
    class pool_allocator_t : allocator_i {
    public:

      struct object_descriptor_t {
        index_t next_idx;
      };

      static constexpr size_t required_size(size_t objectsize, size_t poolsize)
      {
        return poolsize * (objectsize + sizeof(object_descriptor_t));
      }

      pool_allocator_t(uint8_t* memory = nullptr, size_t objectsize = 0, size_t poolsize = 0) :
        descriptors{ reinterpret_cast<object_descriptor_t*>(memory) },
        objects{ reinterpret_cast<uint8_t*>(&descriptors[poolsize]) },
        objectsize{ objectsize },
        poolsize{ poolsize }
        { clear(); }

      void* raw_memory() { return descriptors; }

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
        size_t idx = indexof(ptr);
        if (idx < 0 || poolsize <= idx)
          return -1;
        object_descriptor_t* tmp;
        // find the node pointing to target object
        for (
          tmp = &occupied_slots_anchor;
          tmp->next_idx != -1 && (size_t)tmp->next_idx != idx;
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
        free_slots_anchor.next_idx = -1;
        occupied_slots_anchor.next_idx = -1;

        for (size_t i=0 ; i<poolsize ; ++i)
          descriptors[i].next_idx = i+1;

        if (0 < poolsize)
        {
          free_slots_anchor.next_idx = 0;
          descriptors[poolsize-1].next_idx = -1;
        }
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

      void* get(size_t index)
      {
        return index < poolsize ? objects + (index * objectsize) : nullptr;
      }
      const void* get(size_t index) const
      {
        return index < poolsize ? objects + (index * objectsize) : nullptr;
      }


      struct iterator {
        pool_allocator_t* allocator;
        index_t index;

        void* operator* () { return allocator->get(index); }
        const void* operator* () const { return allocator->get(index); }

        template <typename T>
        T* get() { return (T*)allocator->get(index); }
        template <typename T>
        const T* get() const { return (const T*)allocator->get(index); }

        iterator& operator++ ()
        {
          if (-1 != index)
            index = allocator->descriptors[index].next_idx;
          return *this;
        }

        explicit operator bool() const { return -1 != index; }
        friend bool operator== (const iterator& a, const iterator& b)
        {
          return a.allocator == b.allocator && a.index == b.index;
        }
      };

      iterator begin() { return { this, occupied_slots_anchor.next_index }; }
      iterator end() { return { this, -1 }; }

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
