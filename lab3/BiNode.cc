//
// Created by user24 on 2019/11/14.
//

#ifndef LAB_DS_BINODE_CC
#define LAB_DS_BINODE_CC

#include "BiNode.hh"
#include <algorithm>
#include <memory>
#include <queue>
#include <fstream>

namespace lab3 {

template<typename T>
auto BiNode<T>::create(std::vector<StringKeyValuePair<T>> &kvPairs,
                       const size_t current) -> size_t {
  size_t pos = current;
  if (current < 0 || current == kvPairs.size() - 1) {
    return -1;
  }
  try {
    if (kvPairs[pos].key != "") {
      _left = std::make_unique<Node>(kvPairs[pos]);
      pos = left()->create(kvPairs, pos + 1);
    }
    if (kvPairs[++pos].key != "") {
      _right = std::make_unique<Node>(kvPairs[pos]);
      pos = right()->create(kvPairs, pos + 1);
    }
  } catch (std::exception &e) {
    throw std::runtime_error("Failed to create a tree with the given sequence.");
  }
  return pos;
}

template<typename T>
auto BiNode<T>::preOrder(BiNode::callback cb) -> void {
  if (!cb(*this)) {
    return;
  };
  if (left() != nullptr)
    left()->preOrder(cb);
  if (right() != nullptr)
    right()->preOrder(cb);
};

template<typename T>
auto BiNode<T>::extendedPreOrder(callback node, std::function<void()> extend) -> void {
//  if (key() != "") {
//    f << key() << std::endl;
//    f << val() << std::endl;
//  } else {
//    f << "" << std::endl;
//  }
  node(*this);
  left() != nullptr ? left()->extendedPreOrder(node, extend) : extend();
  right() != nullptr ? right()->extendedPreOrder(node, extend) : extend();
};

template<typename T>
auto BiNode<T>::postOrder(BiNode::callback cb) -> void {
  if (left() != nullptr)
    left()->postOrder(cb);
  if (right() != nullptr)
    right()->postOrder(cb);
  if (!cb(*this)) {
    return;
  };
};

template<typename T>
auto BiNode<T>::inOrder(BiNode::callback cb) -> void {
  if (left() != nullptr)
    left()->inOrder(cb);
  if (!cb(*this)) {
    return;
  };
  if (right() != nullptr)
    right()->inOrder(cb);
};

template<typename T>
auto BiNode<T>::levelOrder(BiNode::callback cb) -> void {
  std::queue<Node *> queue;
  queue.push(this);
  int i = 0;
  while (!queue.empty() && i < 10) {
    i++;
    auto node = queue.front();
    queue.pop();
    if (!cb(*node)) {
      break;
    };
    if (node->left() != nullptr)
      queue.push(node->left());
    if (node->right() != nullptr)
      queue.push(node->right());
  }
};

template<typename T>
auto BiNode<T>::depth() -> size_t {
  if (left() == nullptr) {
    if (right() == nullptr) {
      return 1;
    } else {
      return right()->depth() + 1;
    }
  } else {
    if (right() == nullptr) {
      return left()->depth() + 1;
    } else {
      return std::max(left()->depth(), right()->depth()) + 1;
    }
  }
};

template<typename T>
auto BiNode<T>::insert(std::string const &key, Node *target, Pos pos) -> void {
  preOrder([&](Node &node) {
    if (node._key != key) {
      return true;
    }
    Node *tmp;
    switch (pos) {
      case Pos::Left: {
        tmp = node.left();
        node._left = std::make_unique<Node>(Node{target->_key, target->_val});
        node.left()->_right.reset(tmp);
        break;
      }
      case Pos::Right: {
        tmp = node.right();
        node._right = std::make_unique<Node>(Node{target->_key, target->_val});
        node.right()->_right.reset(tmp);
        break;
      }
      default:break;
    }
    return true;
  });
};

template<typename T>
auto BiNode<T>::autoReset(BiNode<T> *target, BiNode<T> *newAddr) -> void {
  if (left() == target) {
    _left.reset(newAddr);
  } else if (right() == target) {
    _right.reset(newAddr);
  }
}

template<typename T>
auto BiNode<T>::remove(std::string const &key) -> void {
  preOrder([&](Node &node) {
    auto childrenUPtr = std::array<Node *, 2>{node.left(), node.right()};
    auto shouldContinue = true;
    std::for_each(childrenUPtr.begin(), childrenUPtr.end(),
                  [&](Node *childUPtr) {
                    auto child = childUPtr;
                    if (child && child->key() == key) {
                      if (!child->left() && !child->right()) { // Degree 0
                        node.autoReset(child);
                      } else if (child->left() && !child->right()) { // Degree 1
                        node.autoReset(child, child->left());
                        // childUPtr.reset(node.left()->left());
                      } else if (!child->left() && child->right()) { // Degree 1
                        // childUPtr.reset(node.left()->right());
                        node.autoReset(child, child->right());
                      } else if (child->left() && child->right()) { // Degree 2
                        auto tmp2 = child->left();
                        while (tmp2->right()) {
                          tmp2 = tmp2->right();
                        }
                        tmp2->_right = std::move(child->_right);
                        if (node.left() == child) {
                          node._left = std::move(child->_left);
                        } else if (node.right() == child) {
                          node._right = std::move(child->_left);
                        }
                      }
                      shouldContinue = false;
                    }
                  });
    return shouldContinue;
  });
}

template<typename T>
auto BiNode<T>::sibling(std::string const &key) -> Node & {
  Node *res;
  preOrder([&](Node &node) {
    auto children = std::array<Node *, 2>{node.left(), node.right()};
    auto shouldContinue = true;
    std::for_each(children.begin(), children.end(), [&](Node *child) {
      if (child) {
        if (child->left()->key() == key) {
          res = child->right();
          shouldContinue = false;
        } else if (child->right()->key() == key) {
          res = child->left();
          shouldContinue = false;
        }
      }
    });
    return shouldContinue;
  });
  if (res == nullptr) {
    throw std::runtime_error("Sibling not found!");
  }
  return *res;
}
template<typename T>
auto BiNode<T>::assign(std::string const &key, T val) -> bool {
  bool found = false;
  preOrder([&](Node &node) {
    if (node.key() == key) {
      node._val == val;
      found = true;
      return false;
    }
    return true;
  });
  return found;
}

template<typename T>
auto BiNode<T>::locate(std::string const &key) -> Node & {
  Node *res = nullptr;
  preOrder([&](Node &node) {
    if (node.key() == key) {
      res = &node;
      return false;
    }
    return true;
  });
  if (res == nullptr) {
    throw std::runtime_error("Node not found!");
  }
  return *res;
}

} // namespace lab3

#endif // LAB_DS_BINODE_CC
