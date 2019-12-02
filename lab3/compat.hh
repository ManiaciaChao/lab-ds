//
// Created by user24 on 2019/12/1.
//

#pragma once
#ifndef LAB_DS_LAB3_COMPAT_HH_
#define LAB_DS_LAB3_COMPAT_HH_

#include "BiTree.cc"
#include "BiNode.cc"

namespace compat {
using namespace lab3;
using status = int;
const status OK = 1;

template<typename T>
inline status InitBiTree(BiTree<T> *&tree) {
  tree = new BiTree<T>();
  return OK;
}

template<typename T>
inline status CreateBiTree(BiTree<T> *&tree, std::vector<StringKeyValuePair<T>> &kvPairs, size_t current = 0) {
  tree->create(kvPairs, current);
  return OK;
}

template<typename T>
inline status DestroyBiTree(BiTree<T> *&tree) {
  delete tree->root();
  delete tree;
  tree = nullptr;
  return OK;
}

template<typename T>
inline status ClearBiTree(BiTree<T> *&tree) {
  tree->clear();
  return OK;
}

template<typename T>
inline bool BiTreeEmpty(BiTree<T> *&tree) {
  return tree->isEmpty();
}

template<typename T>
inline size_t BiTreeDepth(BiTree<T> *&tree) {
  return tree->depth();
}

template<typename T>
inline BiNode<T> *LocateNode(BiTree<T> *&tree, std::string &key) {
  return &tree->locate(key);
}

template<typename T>
inline bool Assign(BiTree<T> *&tree, std::string &key, T val) {
  return tree->assign(key, val);
}

template<typename T>
inline BiNode<T> *GetSibling(BiTree<T> *&tree, std::string &key) {
  return &tree->sibling(key);
}

template<typename T>
inline status InsertNode(BiTree<T> *&tree, std::string &key, Pos pos, BiNode<T> *target) {
  tree->insert(key, target, pos);
  return OK;
}

template<typename T>
inline status DeleteNode(BiTree<T> *&tree, std::string &key) {
  tree->remove(key);
  return OK;
}

template<typename T>
inline status PreOrderTraverse(BiTree<T> *&tree, std::function<bool(BiNode<T> &)> visit) {
  tree->preOrder(visit);
  return OK;
}

template<typename T>
inline status InOrderTraverse(BiTree<T> *&tree, std::function<bool(BiNode<T> &)> visit) {
  tree->inOrder(visit);
  return OK;
}

template<typename T>
inline status PostOrderTraverse(BiTree<T> *&tree, std::function<bool(BiNode<T> &)> visit) {
  tree->postOrder(visit);
  return OK;
}

template<typename T>
inline status LevelOrderTraverse(BiTree<T> *&tree, std::function<bool(BiNode<T> &)> visit) {
  tree->levelOrder(visit);
  return OK;
}

}

#endif //LAB_DS_LAB3_COMPAT_HH_
