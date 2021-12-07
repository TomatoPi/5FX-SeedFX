#pragma once

namespace sfx
{
  namespace utils
  {
    template <typename T>
    struct lnode_t {
      T obj;
      lnode_t* next;

      T& get() { return obj; }
      const T& get() const { return obj; }
    };

    /// Double linked anchored list
    template <typename Node>
    class llist_t {
    public :

      llist_t() : list{nullptr} {}

      static void init(Node* node)
      {
        node->next = node;
      }

      void push_back(Node* node)
      {

      }
      void push_front(Node* node)
      {
        node->next = list;
        list = node;
      }

      template <typename Predicate>
      Node** find(const Predicate& predicate)
      {
        for (Node** node = &list; *node != nullptr; node = &(node->next))
          if (predicate(*node))
            return node;
        return nullptr;
      }

      auto& front() { return begin()->get(); }
      const auto& front() const { return begin()->get(); }

      Node* begin() { return list; }
      const Node* begin() const { return list; }

      Node* end() { return nullptr; }
      const Node* end() const { return nullptr; }

    private:
      Node* list;
    };

  }
  // namespace utils
}
// namespace sfx