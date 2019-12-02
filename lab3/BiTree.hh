//
// Created by user24 on 2019/11/14.
//

#pragma once
#ifndef LAB_DS_LAB3_BITREE_HH_
#define LAB_DS_LAB3_BITREE_HH_

#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include "BiNode.hh"

namespace lab3 {

template<typename T>
class BiTree {
  using Node = BiNode<T>;
  using callback = std::function<bool(Node &)>;

 private:
  std::unique_ptr<Node> _root;
 private:
  inline auto checkRoot() -> void {
    root() == nullptr ? throw std::runtime_error("Illegal operation on a tree without root!") : true;
  }

 public:
  inline auto root() -> Node * { return _root.get(); }
  inline auto isEmpty() { return root() == nullptr; }
  inline auto depth() -> std::size_t { return checkRoot(), root()->depth(); }
  auto length() -> size_t;

 public:
  BiTree() : _root(nullptr) {};
  BiTree(std::initializer_list<T> i) : _root(std::make_unique<Node>) {};

  // Construct a tree extended pre-order
  auto create(std::vector<StringKeyValuePair<T>> &kvPairs, size_t current = 0) -> size_t;

  inline auto clear() -> void { _root.reset(nullptr); }
  inline auto remove(std::string &key) -> void { checkRoot(), root()->remove(key); };
  inline auto sibling(std::string &key) -> Node & { return checkRoot(), root()->sibling(key); };
  inline auto assign(std::string &key, T val) -> bool { return checkRoot(), root()->assign(key, val); };
  inline auto insert(std::string &key, Node *node, Pos pos) -> void { checkRoot(), root()->insert(key, node, pos); };
  inline auto locate(std::string &key) -> Node & { return checkRoot(), root()->locate(key); };

  inline auto preOrder(callback cb) -> void { checkRoot(), root()->preOrder(cb); };
  inline auto inOrder(callback cb) -> void { checkRoot(), root()->inOrder(cb); };
  inline auto postOrder(callback cb) -> void { checkRoot(), root()->postOrder(cb); };
  inline auto levelOrder(callback cb) -> void { checkRoot(), root()->levelOrder(cb); };

  auto save(std::string const &) -> void;
  auto load(std::string const &) -> void;

};

}

#endif //LAB_DS_LAB3_BITREE_HH_
