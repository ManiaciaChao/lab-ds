//
// Created by user24 on 2019/12/17.
//

#ifndef LAB_DS_LAB4_COMPAT_HH_
#define LAB_DS_LAB4_COMPAT_HH_

#include "Graph.cc"

namespace compat {
using namespace lab4;
using status = int;
const status OK = 1;

template<typename T>
inline status InitGraph(Graph<T> *&graph) {
  graph = new Graph<T>();
  return OK;
}

template<typename T>
inline status CreateGraph(Graph<T> *&graph, std::vector<Vertex<T>> vertices, const std::vector<ArcPair> &arcs) {
  graph = new Graph<T>(vertices, arcs);
  return OK;
}

template<typename T>
inline status DestroyGraph(Graph<T> *&graph) {
  delete graph;
  graph = nullptr;
  return OK;
}

template<typename T>
inline Vertex<T> *LocateVex(Graph<T> *&graph, const Key &key) {
  return &graph->locate(key);
}

template<typename T>
inline status PutVex(Graph<T> *&graph, const Key &key, T val) {
  graph->assign(key, val);
  return OK;
}

template<typename T>
inline Vertex<T> *FirstAdjVex(Graph<T> *&graph, const Key &key) {
  return &graph->firstAdj(key);
}

template<typename T>
inline Vertex<T> *NextAdjVex(Graph<T> *&graph, const Key &key, const Key &after) {
  return &graph->nextAdj(key, after);
}

template<typename T>
inline status InsertVex(Graph<T> *&graph, Vertex<T> *vertex) {
  graph->insert(*vertex);
  return OK;
}

template<typename T>
inline status DeleteVex(Graph<T> *&graph, const Key &key) {
  graph->remove(key);
  return OK;
}

template<typename T>
inline status InsertArc(Graph<T> *&graph, const Key &from, const Key &to) {
  graph->link(from, to);
  return OK;
}

template<typename T>
inline status DeleteArc(Graph<T> *&graph, const Key &from, const Key &to) {
  graph->unlink(from, to);
  return OK;
}

template<typename T>
inline status DFSTraverse(Graph<T> *&graph, typename Graph<T>::callback cb) {
  graph->dfs(cb);
  return OK;
}

template<typename T>
inline status BFSTraverse(Graph<T> *&graph, typename Graph<T>::callback cb) {
  graph->bfs(cb);
  return OK;
}

}

#endif //LAB_DS_LAB4_COMPAT_HH_
