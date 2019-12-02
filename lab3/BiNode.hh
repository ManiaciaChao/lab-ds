//
// Created by user24 on 2019/11/14.
//

#ifndef LAB_DS_BINODE_HH
#define LAB_DS_BINODE_HH

#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace lab3 {

enum class Pos { Left, Right };

template <typename T> struct StringKeyValuePair {
  std::string key;
  T val;
};
template <typename T> class BiNode {
  using Node = BiNode<T>;
  using callback = std::function<bool(Node &)>;

private:
  T _val;
  const std::string _key;
  std::unique_ptr<Node> _left, _right;
  auto autoReset(Node *target, Node *newAddr = nullptr) -> void;

public:
  BiNode() : _left(nullptr), _right(nullptr), _val(), _key(""){};
  explicit BiNode(std::string key, T val)
      : _left(nullptr), _right(nullptr), _key(std::move(key)), _val(val){};
  explicit BiNode(StringKeyValuePair<T> kvp)
      : _left(nullptr), _right(nullptr), _key(kvp.key), _val(kvp.val){};
  //  BiNode(const Node &node)
  //      : _left(std::move(node._left)), _right(std::move(node._right)),
  //      _val(node._val), _key(node._key) {};
  //  BiNode(const Node &node) {
  //    _left=nullptr;
  //    _right=nullptr;
  //    _val=node._val;
  //    _key=std::move(node._key);
  //  }

  inline auto create(std::vector<StringKeyValuePair<T>> &, size_t = 0)
      -> size_t;

  inline auto left() const { return _left.get(); }
  inline auto right() const { return _right.get(); }
  inline auto val() -> const T & { return _val; }
  [[nodiscard]] inline auto key() const -> const std::string & { return _key; }

  auto depth() -> size_t;
  auto preOrder(callback) -> void;
  auto inOrder(callback) -> void;
  auto postOrder(callback) -> void;
  auto levelOrder(callback) -> void;
  auto extendedPreOrder(callback,std::function<void()>) -> void;


  auto insert(std::string const &key, Node *node, Pos pos) -> void;
  auto remove(std::string const &key) -> void;
  auto locate(std::string const &key) -> Node &;
  auto assign(std::string const &key, T val) -> bool;

  auto sibling(std::string const &key) -> Node &;

};
};     // namespace lab3
#endif // LAB_DS_BINODE_HH
