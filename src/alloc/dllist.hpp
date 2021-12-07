#pragma once

namespace sfx
{
  namespace utils
  {
    template <typename T>
    struct dlnode_t {
      T obj;
      dlnode_t* next;
      dlnode_t* prev;

      T& get() { return obj; }
      const T& get() const { return obj; }
    };

    /// Double linked anchored list
    template <typename Node>
    class dllist_t {
    public :

      dllist_t() { anchor.next = anchor.prev = &anchor; }

      static void init(Node* node)
      {
        node->next = node->prev = node;
      }
      static void extract(Node* node)
      {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node->next = node->prev = node;
      }
      static void insert_before(Node* node, Node* other)
      {
        node->next = other;
        node->prev = other->prev;
        other->prev->next = node;
        other->prev = node;
      }

      void push_back(Node* node)
      {
        insert_before(node, end());
      }
      void push_front(Node* node)
      {
        insert_before(node, begin());
      }

      template <typename T>
      Node* find(const T& obj)
      {
        for (Node* node = begin(); node != end(); node = node->next)
          if (node->get() == obj)
            return node;
        return nullptr;
      }

      auto& front() { return begin()->get(); }
      const auto& front() const { return begin()->get(); }

      auto& back() { return end()->prev->get(); }
      const auto& back() const { return end()->prev->get(); }

      Node* begin() { return anchor.next; }
      const Node* begin() const { return anchor.next; }

      Node* end() { return &anchor; }
      const Node* end() const { return &anchor; }

    private:
      Node anchor;
    };

  }
  // namespace utils
}
// namespace sfx