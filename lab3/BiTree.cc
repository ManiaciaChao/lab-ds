//
// Created by user24 on 2019/11/16.
//

#ifndef LAB_DS_LAB3_BITREE_CC
#define LAB_DS_LAB3_BITREE_CC

#include <fstream>
#include "BiTree.hh"
#include "BiNode.hh"

namespace lab3 {

template<typename T>
auto BiTree<T>::length() -> size_t {
  size_t length = 0;
  preOrder([&length](Node &node) {
    return length++, true;
  });
  return length;
}

template<typename T>
auto BiTree<T>::create(std::vector<lab3::StringKeyValuePair<T>> &kvPairs, size_t const current) -> size_t {
  if (current < 0 || current == kvPairs.size() - 1 || kvPairs[current].key == "") { return -1; }
  _root = std::make_unique<Node>(kvPairs[current]);
  return root()->create(kvPairs, current + 1);
}

template<typename T>
auto BiTree<T>::save(std::string const &filename) -> void {
  std::ofstream f;
  f.open(filename);
  size_t extendedLength = 0;
  root()->extendedPreOrder([&extendedLength](Node &node) { return extendedLength++, true; },
                           [&extendedLength] { extendedLength++; });

  f << extendedLength << std::endl;
  root()->extendedPreOrder(
      [&f](Node &node) {
        if (node.key() != "") {
          f << node.key() << std::endl;
          f << node.val() << std::endl;
        } else {
          f << "" << std::endl;
        }
        return true;
      },
      [&f] { f << "" << std::endl; }
  );
  f.close();
}

template<typename T>
auto BiTree<T>::load(std::string const &filename) -> void {
  using KVP = StringKeyValuePair<T>;
  std::fstream f(filename, std::ios_base::in);
  size_t len = 0;
  f >> len;
  f.get();
  std::vector<KVP> kvPairs;
  for (size_t i = 0; i < len; i++) {
    std::string key;
    T val = 0;
//    f >> key;
    std::getline(f, key);
    if (!key.empty()) {
      f >> val;
      f.get();
//      std::getline(f, val);
    }
    kvPairs.push_back(KVP{key, val});
  }
  f.close();
  create(kvPairs);
}

}

#endif //LAB_DS_LAB3_BITREE_CC
