#pragma once

#include "dllist.hpp"

#include <stddef.h>
#include <stdint.h>

namespace sfx
{
  namespace utils
  {
    class allocator_t {
    public:

      struct memblock_desc_t {
        memblock_desc_t*  next;
        size_t blocksize;

        /// Small hack, this +1 return the first address after this struct,
        ///   which is the memory block itself
        void* memblock() { return this +1; }
        const void* memblock() const { return this +1; }

        memblock_desc_t* next_contiguous_block() const
        {
          return (memblock_desc_t*)(((uint8_t*)memblock()) + blocksize);
        }
      };

      allocator_t(uint8_t* memory, size_t memsize) :
        memory{ memory }, memsize{ memsize },
        free_blocks_anchor{ reinterpret_cast<memblock_desc_t*>(memory), 0 },
        occupied_blocks_anchor{ nullptr, 0 }
      {
        clear();
      }

      void* alloc(size_t size) 
      {
        memblock_desc_t** block_ptr = firstblock_big_enought_for(size);
        if (nullptr == block_ptr || nullptr == *block_ptr)
          return nullptr;
        
        // fit the block
        memblock_desc_t* newblock = *block_ptr;
        memblock_desc_t* garbage = reduce_block_size(newblock, size);

        // put the block in occupied list
        memblock_desc_t* tmp = newblock->next;
        newblock->next = occupied_blocks_anchor.next;
        occupied_blocks_anchor.next = newblock;
        *block_ptr = tmp;
        
        if (nullptr != garbage)
        {
          garbage->next = free_blocks_anchor.next;
          free_blocks_anchor.next = garbage;
        }

        // return ptr to allocated memory
        return newblock->memblock();
      }

      int free(void* ptr)
      {
        memblock_desc_t** desc_ptr = owner_of(ptr);
        if (nullptr == desc_ptr || nullptr == *desc_ptr)
          return -1;
        
        // then put the descriptor back to free list
        memblock_desc_t* freedblock =  *desc_ptr;
        memblock_desc_t* tmp = freedblock->next;
        freedblock->next = free_blocks_anchor.next;
        free_blocks_anchor.next = freedblock;
        *desc_ptr = tmp;

        return 0;
      }

      void clear()
      {
        occupied_blocks_anchor.blocksize = 0;
        occupied_blocks_anchor.next = nullptr;

        free_blocks_anchor.blocksize = 0;
        free_blocks_anchor.next = reinterpret_cast<memblock_desc_t*>(memory);

        memblock_desc_t* firstblock = free_blocks_anchor.next;
        firstblock->blocksize = memsize - sizeof(memblock_desc_t);
        firstblock->next = nullptr;
      }

      size_t max_available_size() const
      {
        size_t max = 0;
        for (
          memblock_desc_t* tmp = free_blocks_anchor.next;
          tmp != nullptr;
          tmp = tmp->next)
        {
          if (max < tmp->blocksize)
            max = tmp->blocksize;
        }
        return max;
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
          if (size <= (*tmp)->blocksize)
            return tmp;
        }
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
        if (block->blocksize < newsize + sizeof(memblock_desc_t))
          return nullptr;
        // compute created block size
        size_t old_blocksize = block->blocksize;
        size_t remaining_mem = old_blocksize - newsize - sizeof(memblock_desc_t);
        // reduce block size
        block->blocksize = newsize;
        // create the new free block
        memblock_desc_t* newblock = block->next_contiguous_block();
        newblock->blocksize = remaining_mem;
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
