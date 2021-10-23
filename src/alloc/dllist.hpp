#pragma once

namespace sfx
{
  namespace utils
  {
    /// Double linked anchored list
    class dllist_t {
    public :
      struct node_t {
        node_t(void* obj = nullptr) : 
          obj{obj}, next{this}, prev{this} {}

        void extract()
        {
          next->prev = prev;
          prev->next = next;
          next = prev = this;
        }

        void* obj;
        node_t* next;
        node_t* prev;
      };

      void add(node_t* node)
      {
        node->next = &anchor;
        node->prev = anchor.prev;
        anchor.prev->next = node;
        anchor.prev = node;
      }

      node_t* begin() { return anchor.next; }
      const node_t* begin() const { return anchor.next; }

      node_t* end() { return &anchor; }
      const node_t* end() const { return &anchor; }

    private:
      node_t anchor;
    };
  }
  // namespace utils
}
// namespace sfx