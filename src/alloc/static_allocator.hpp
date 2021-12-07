#pragma once

#include <cstdint>
#include <cstdio>

namespace sfx
{
  namespace alloc
  {
    struct memblock_desc_t {
      memblock_desc_t*  next;
      int16_t signed_blocksize;

      /// Small hack, this +1 return the first address after this struct,
      ///   which is the memory block itself
      void*       memblock()       { return this +1; }
      const void* memblock() const { return this +1; }

      uint32_t blocksize() const
      {
        return signed_blocksize < 0 ? -signed_blocksize : signed_blocksize;
      }

      bool is_free() const { return signed_blocksize < 0; }

      memblock_desc_t* next_contiguous_block() const
      {
        return (memblock_desc_t*)(((uint8_t*)memblock()) + blocksize());
      }
    };

    struct mem_desc_t {
      memblock_desc_t* free_lst;
      memblock_desc_t* occupied_lst;
    };

    class heterogenous_mempool_adaptator_t {
    public:

      heterogenous_mempool_adaptator_t(uint8_t* memory, uint32_t memsize) :
        rawmemory{nullptr}, rawmemsize{0}
      {
        if (mem_is_valid(memory, memsize))
        {
          rawmemory = memory;
          rawmemsize = memsize;
        }
      }

      void* alloc(uint32_t size)
      {
        memblock_desc_t** block_ptr = firstblock_big_enought_for(size);
        if (nullptr == block_ptr || nullptr == *block_ptr)
          return nullptr;
        
        // fit the block
        memblock_desc_t* newblock = *block_ptr;
        memblock_desc_t* garbage = reduce_block_size(newblock, size);

        // put the block in occupied list
        memblock_desc_t* tmp = newblock->next;
        newblock->signed_blocksize = newblock->blocksize();
        newblock->next = header()->occupied_lst;
        header()->occupied_lst = newblock;
        *block_ptr = tmp;
        
        if (nullptr != garbage)
        {
          garbage->signed_blocksize = -garbage->blocksize();
          garbage->next = header()->free_lst;
          header()->free_lst = garbage;
        }

        fprintf(stderr, "Allocated %u bytes in memblock %p\n", size, this);
        // return ptr to allocated memory
        return newblock->memblock();
      }

      int free(void* ptr)
      {
        if (nullptr == ptr)
          return 0;
        
        memblock_desc_t** desc_ptr = owner_of(ptr);
        if (nullptr == desc_ptr || nullptr == *desc_ptr)
          return -1;

        fprintf(stderr, "Freed %u bytes in memblock %p\n", (*desc_ptr)->blocksize(), this);
        
        // then put the descriptor back to free list
        memblock_desc_t* freedblock =  *desc_ptr;
        memblock_desc_t* tmp = freedblock->next;
        freedblock->next = header()->free_lst;
        header()->free_lst = freedblock;
        freedblock->signed_blocksize = -freedblock->blocksize();
        *desc_ptr = tmp;

        return 0;
      }

      void clear()
      {
        if (sizeof(memblock_desc_t) < memsize())
        {
          mem_desc_t* head = header();

          head->free_lst = reinterpret_cast<memblock_desc_t*>(memory());
          head->occupied_lst = nullptr;

          memblock_desc_t* firstblock = head->free_lst;
          firstblock->signed_blocksize = memsize() - sizeof(memblock_desc_t);
          firstblock->signed_blocksize = -firstblock->blocksize();
          firstblock->next = nullptr;
        }
      }

      void optimize_memory()
      {
        if (nullptr == rawmemory)
          return;
        
        memblock_desc_t** free_ptr = &header()->free_lst;
        memblock_desc_t** occupied_ptr = &header()->occupied_lst;
        
        for (
          memblock_desc_t* tmp = reinterpret_cast<memblock_desc_t*>(memory());
          (uint8_t*)tmp < memory() + memsize();
          tmp = tmp->next_contiguous_block())
        {
          if (tmp->is_free())
          {
            memblock_desc_t* merge_candidate = tmp->next_contiguous_block();
            while (merge_candidate->is_free())
            {
              tmp->signed_blocksize -= merge_candidate->blocksize();
              tmp->signed_blocksize -= sizeof(memblock_desc_t);
              merge_candidate = tmp->next_contiguous_block();
            }
            *free_ptr = tmp;
            free_ptr = &tmp->next;
          }
          else // tmp is in use
          {
            *occupied_ptr = tmp;
            occupied_ptr = &tmp->next;
          }
        }
        // close both lists
        *free_ptr = *occupied_ptr = nullptr;
      }

      uint32_t max_available_size() const
      {
        if (nullptr == rawmemory)
          return 0;
        
        uint32_t max = 0;
        for (
          memblock_desc_t* tmp = header()->free_lst;
          tmp != nullptr;
          tmp = tmp->next)
        {
          if (max < tmp->blocksize())
            max = tmp->blocksize();
        }
        return max;
      }
      uint32_t total_available_size() const
      {
        if (nullptr == rawmemory)
          return 0;
        
        uint32_t res = 0;
        for (
          memblock_desc_t* tmp = header()->free_lst;
          tmp != nullptr;
          tmp = tmp->next)
        {
          res += tmp->blocksize();
        }
        return res;
      }

      const memblock_desc_t* freelst() const { return rawmemory ? header()->free_lst : nullptr; }
      const memblock_desc_t* alloclst() const { return rawmemory ? header()->occupied_lst : nullptr; }

      friend bool operator== (const heterogenous_mempool_adaptator_t& a, const heterogenous_mempool_adaptator_t& b)
      {
        return a.rawmemory == b.rawmemory;
      }

    private:

      static constexpr bool mem_is_valid(const uint8_t* mem, uint32_t size)
      {
        return nullptr != mem && mem_offset() <= size;
      }
      static constexpr uint32_t mem_offset() { return sizeof(mem_desc_t); }

      mem_desc_t*       header()       { return reinterpret_cast<mem_desc_t*>(rawmemory); }
      const mem_desc_t* header() const { return reinterpret_cast<const mem_desc_t*>(rawmemory); }

      uint8_t*       memory()       { return rawmemory + mem_offset(); }
      const uint8_t* memory() const { return rawmemory + mem_offset(); }

      uint32_t memsize() const { return rawmemsize < mem_offset() ? 0 : rawmemsize - mem_offset(); }

      memblock_desc_t** firstblock_big_enought_for(uint32_t size)
      {
        if (nullptr == rawmemory)
          return nullptr;
          
        for (
          memblock_desc_t** tmp = &header()->free_lst;
          tmp != nullptr && *tmp != nullptr;
          tmp = &((*tmp)->next))
        {
          if (size <= (*tmp)->blocksize())
            return tmp;
        }
        // out_of_memory(this, size, max_available_size());
        return nullptr;
      }

      memblock_desc_t** owner_of(void* ptr)
      {
        if (nullptr == rawmemory)
          return nullptr;

        for (
          memblock_desc_t** tmp = &header()->occupied_lst;
          tmp != nullptr && *tmp != nullptr;
          tmp = &((*tmp)->next))
        {
          if (ptr == (*tmp)->memblock())
            return tmp;
        }
        return nullptr;
      }

      memblock_desc_t* reduce_block_size(memblock_desc_t* block, uint32_t newsize)
      {
        // To split a block, we need at least some place to
        //  store the next descriptor 
        if (block->blocksize() < newsize + sizeof(memblock_desc_t))
          return nullptr;
        // compute created block size
        uint32_t old_blocksize = block->blocksize();
        uint32_t remaining_mem = old_blocksize - newsize - sizeof(memblock_desc_t);
        // reduce block size
        block->signed_blocksize = newsize;
        // create the new free block
        memblock_desc_t* newblock = block->next_contiguous_block();
        newblock->signed_blocksize = remaining_mem;
        newblock->signed_blocksize = -newblock->blocksize();
        // done
        return newblock;
      }

      uint8_t* rawmemory;
      uint32_t rawmemsize;
    };

    template <class T, heterogenous_mempool_adaptator_t* Mem>
    struct static_allocator
    {
      typedef T value_type;

      template<class U>
      struct rebind { using other = static_allocator<U, Mem>; };  
    
      static_allocator () = default;
      template <class U> constexpr static_allocator(const static_allocator<U, Mem>&) noexcept {}
    
      [[nodiscard]] T* allocate(std::size_t n) {
        return (T*) Mem->alloc(n * sizeof(T));
      }
    
      void deallocate(T* p, std::size_t n) noexcept {
        Mem->free(p);
      }
    };
    
    template <
      class T, heterogenous_mempool_adaptator_t* MemA,
      class U, heterogenous_mempool_adaptator_t* MemB>
    bool operator==(const static_allocator<T, MemA>&, const static_allocator<U, MemB>&)
    {
      return MemA == MemB;
    }
    template <
      class T, heterogenous_mempool_adaptator_t* MemA,
      class U, heterogenous_mempool_adaptator_t* MemB>
    bool operator!=(const static_allocator<T, MemA>&, const static_allocator<U, MemB>&)
    {
      return MemA != MemB;
    }
  }
  // namespace alloc
}
// namespace sfx
