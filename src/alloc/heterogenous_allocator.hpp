#pragma once

#include "alloc.hpp"

#include <stddef.h>
#include <stdint.h>

namespace sfx
{
  namespace alloc
  {
    class heterogenous_allocator_t : public allocator_i {
    public:

      struct memblock_desc_t {
        memblock_desc_t*  next;
        int16_t signed_blocksize;

        /// Small hack, this +1 return the first address after this struct,
        ///   which is the memory block itself
        void* memblock() { return this +1; }
        const void* memblock() const { return this +1; }

        size_t blocksize() const
        {
          return signed_blocksize < 0 ? -signed_blocksize : signed_blocksize;
        }

        bool is_free() const { return signed_blocksize < 0; }

        memblock_desc_t* next_contiguous_block() const
        {
          return (memblock_desc_t*)(((uint8_t*)memblock()) + blocksize());
        }
      };

      heterogenous_allocator_t(uint8_t* memory, size_t memsize) :
        memory{ memory }, memsize{ memsize },
        free_blocks_anchor{ reinterpret_cast<memblock_desc_t*>(memory), 0 },
        occupied_blocks_anchor{ nullptr, 0 }
      {
        clear();
      }

      void* alloc(size_t size) override
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
        newblock->next = occupied_blocks_anchor.next;
        occupied_blocks_anchor.next = newblock;
        *block_ptr = tmp;
        
        if (nullptr != garbage)
        {
          garbage->signed_blocksize = -garbage->blocksize();
          garbage->next = free_blocks_anchor.next;
          free_blocks_anchor.next = garbage;
        }

        fprintf(stderr, "Allocated %lu bytes in memblock %p\n", size, this);
        // return ptr to allocated memory
        return newblock->memblock();
      }

      int free(void* ptr) override
      {
        memblock_desc_t** desc_ptr = owner_of(ptr);
        if (nullptr == desc_ptr || nullptr == *desc_ptr)
          return -1;
        
        // then put the descriptor back to free list
        memblock_desc_t* freedblock =  *desc_ptr;
        memblock_desc_t* tmp = freedblock->next;
        freedblock->next = free_blocks_anchor.next;
        free_blocks_anchor.next = freedblock;
        freedblock->signed_blocksize = -freedblock->blocksize();
        *desc_ptr = tmp;

        return 0;
      }

      void clear() override
      {
        occupied_blocks_anchor.signed_blocksize = 0;
        occupied_blocks_anchor.next = nullptr;

        free_blocks_anchor.signed_blocksize = 0;
        free_blocks_anchor.next = nullptr;

        if (0 < memsize)
        {
          free_blocks_anchor.next = reinterpret_cast<memblock_desc_t*>(memory);

          memblock_desc_t* firstblock = free_blocks_anchor.next;
          firstblock->signed_blocksize = memsize - sizeof(memblock_desc_t);
          firstblock->signed_blocksize = -firstblock->blocksize();
          firstblock->next = nullptr;
        }
      }

      void optimize_memory()
      {
        memblock_desc_t** free_ptr = &free_blocks_anchor.next;
        memblock_desc_t** occupied_ptr = &occupied_blocks_anchor.next;
        
        for (
          memblock_desc_t* tmp = reinterpret_cast<memblock_desc_t*>(memory);
          (uint8_t*)tmp < memory + memsize;
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

      size_t max_available_size() const
      {
        size_t max = 0;
        for (
          memblock_desc_t* tmp = free_blocks_anchor.next;
          tmp != nullptr;
          tmp = tmp->next)
        {
          if (max < tmp->blocksize())
            max = tmp->blocksize();
        }
        return max;
      }
      size_t total_available_size() const
      {
        size_t res = 0;
        for (
          memblock_desc_t* tmp = free_blocks_anchor.next;
          tmp != nullptr;
          tmp = tmp->next)
        {
          res += tmp->blocksize();
        }
        return res;
      }

      const memblock_desc_t* freelst() const { return free_blocks_anchor.next; }
      const memblock_desc_t* alloclst() const { return occupied_blocks_anchor.next; }

    private:

      memblock_desc_t** firstblock_big_enought_for(size_t size)
      {
        for (
          memblock_desc_t** tmp = &(free_blocks_anchor.next);
          tmp != nullptr && *tmp != nullptr;
          tmp = &((*tmp)->next))
        {
          if (size <= (*tmp)->blocksize())
            return tmp;
        }
        out_of_memory(this, size, max_available_size());
        return nullptr;
      }

      memblock_desc_t** owner_of(void* ptr)
      {
        for (
          memblock_desc_t** tmp = &(occupied_blocks_anchor.next);
          tmp != nullptr && *tmp != nullptr;
          tmp = &((*tmp)->next))
        {
          if (ptr == (*tmp)->memblock())
            return tmp;
        }
        return nullptr;
      }

      memblock_desc_t* reduce_block_size(memblock_desc_t* block, size_t newsize)
      {
        // To split a block, we need at least some place to
        //  store the next descriptor 
        if (block->blocksize() < newsize + sizeof(memblock_desc_t))
          return nullptr;
        // compute created block size
        size_t old_blocksize = block->blocksize();
        size_t remaining_mem = old_blocksize - newsize - sizeof(memblock_desc_t);
        // reduce block size
        block->signed_blocksize = newsize;
        // create the new free block
        memblock_desc_t* newblock = block->next_contiguous_block();
        newblock->signed_blocksize = remaining_mem;
        newblock->signed_blocksize = -newblock->blocksize();
        // done
        return newblock;
      }

      uint8_t* memory;
      const size_t memsize;

      memblock_desc_t free_blocks_anchor;
      memblock_desc_t occupied_blocks_anchor;
    };
  }
  // namespace utils
}
// namespace sfx
