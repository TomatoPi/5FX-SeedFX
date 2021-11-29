#pragma once

namespace sfx
{
  namespace utils
  {
    /// Double linked anchored list
    template <typename T>
    class dllist_t {
    public :

      struct node_t {
        node_t(T obj = T()) : 
          obj{obj}, next{this}, prev{this} {}

        void extract()
        {
          next->prev = prev;
          prev->next = next;
          next = prev = this;
        }
        static void insert_before(node_t* node, node_t* other)
        {
          node->next = other;
          node->prev = other->prev;
          other->prev->next = node;
          other->prev = node;
        }

        T obj;
        node_t* next;
        node_t* prev;
      };

      dllist_t() { anchor.next = anchor.prev = &anchor; }

      void push_back(node_t* node)
      {
        node_t::insert_before(node, end());
      }
      void push_front(node_t* node)
      {
        node_t::insert_before(node, begin());
      }

      node_t* find(const T& obj)
      {
        for (node_t* node = begin(); node != end(); node = node->next)
          if (node->obj == obj)
            return node;
        return nullptr;
      }

      T& front() { return begin()->obj; }
      const T& front() const { return begin()->obj; }

      T& back() { return end()->prev->obj; }
      const T& back() const { return end()->prev->obj; }

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