#pragma once

#include <stdint.h>
#include <stddef.h>

namespace sfx
{
  namespace hw
  {
    /// Object used to describe how an object is structured
    ///   in order to serialise it
    struct layout_descriptor {

      size_t fragment_offset = 0; ///!< Offset from object address
      size_t fragment_size = 0;   ///!< 0 if object has a dynamic size
      size_t (*fragment_dynamic_size)(void* obj) = nullptr;
      
      bool fragment_is_ptr = false; ///!< true if fragment describe a pointer

      bool fragment_is_composite = false;
      layout_descriptor* composite_fragment = nullptr;

      layout_descriptor* next_fragment = nullptr; ///!< linked list
    };

    template <typename T, size_t size>
    struct standard_layout {
      static constexpr const size_t fragment_size = sizeof(T);
      static constexpr const size_t fragment_real_size = sizeof(T);
    };

    template <typename T, size_t (*dynamic_size)(void*)>
    struct ptr_layout {
      static constexpr const size_t (*fragment_size)(void*) = dynamic_size;
      static constexpr const size_t fragment_real_size = sizeof(void*);
    };

    namespace impl
    {
      template <typename T, size_t offset>
      const layout_descriptor* make_descriptor() { return nullptr; }

      template <typename T, size_t offset, typename Helper>
      const layout_descriptor* make_descriptor() { return nullptr; }

      template <typename T, size_t offset, size_t size>
      const layout_descriptor* make_descriptor<T, size, standard_layout<T, size>>()
      {
        static layout_descriptor blk {
          offset,
          size,
          nullptr,

          false,

          false, nullptr,

          make_descriptor<T, offset + size, >
        };
        return &blk;
      }

    }
    // namespace impl

    template <typename T, typename Helper, typename ...Helpers>
    const layout_descriptor* make_descriptor()
    {
      return impl::make_descriptor<T, Helper, Helpers...>();
    }

    template <typename T>
    const layout_descriptor* layout_of()
    {
      static layout_descriptor desc{ 0, sizeof(T), nullptr, false, nullptr };
      return &desc;
    }

    /// Object used to represent a serialised object
    struct byte_stream {
      uint8_t* stream = nullptr;
      size_t size = 0;
    };
  }
  // namespace hw
}
// namespace sfx