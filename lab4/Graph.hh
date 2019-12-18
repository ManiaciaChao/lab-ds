//
// Created by user24 on 2019/12/9.
//

#ifndef LAB_DS_LAB4_GRAPH_HH_
#define LAB_DS_LAB4_GRAPH_HH_

#include <functional>
#include <memory>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <utility>

namespace lab4 {

using Key = std::string;

template<typename T>
class Graph;
template<typename T>
class Vertex;
template<typename T>
class Adjacent;

struct ArcPair {
  Key from;
  Key to;
};

template<typename T>
class Graph {

 private:
  std::unordered_map<std::string, Vertex<T>> _nodes;

 public:
  using callback = std::function<bool(Vertex<T> &)>;

  struct Separator {
    char Link = '&';
    char Val = ':';
    char And = ',';
  } separator;

 public:
  Graph() : _nodes() {}
  Graph(std::vector<Vertex<T>> &vertices);
  Graph(std::vector<Vertex<T>> &vertices, std::vector<ArcPair> &arcs);
  auto locate(const Key &key) -> Vertex<T> &;
  auto assign(const Key &key, T val) -> void;
  auto firstAdj(const Key &key) -> Vertex<T> &;
  auto nextAdj(const Key &key, const Key &after) -> Vertex<T> &;
  auto insert(Vertex<T> &) -> void;
  auto remove(const Key &) -> void;
  auto link(const Key &from, const Key &to) -> void;
  auto unlink(const Key &from, const Key &to) -> void;
  auto dfs(callback) -> void;
  auto bfs(callback) -> void;

  auto save(const std::string &filename) -> void;
  auto load(const std::string &filename) -> void;
//  template<typename StreamType>
//  auto load(StreamType & stream ) -> void;
  auto load(std::basic_istream<char> &stream) -> void;

//  auto traverse(callback) -> void;
};

template<typename T>
class Vertex {
  friend class Graph<T>;
 private:
  T _val;
  Key _key;
  std::unique_ptr<Adjacent<T>> _next;
  auto has(Key) -> bool;
 public:
  using callback = std::function<bool(Adjacent<T> &)>;
  Vertex(Key key, T val) : _key(std::move(key)), _val(val) {};
  Vertex(const Vertex &vertex) : _key(std::move(vertex._key)), _val(vertex._val) {};
  inline auto key() { return _key; };
  inline auto val() { return _val; };
  auto traverse(callback) const -> void;

};

template<typename T>
class Adjacent {
  friend class Graph<T>;
  friend class Vertex<T>;
 private:
  std::unique_ptr<Adjacent<T>> _next;
 public:
  Key _key;
  using callback = std::function<bool(Adjacent<T> &)>;
  explicit Adjacent<T>(Key &key) : _key(key), _next(nullptr) {};
  Adjacent<T>(Key key, std::unique_ptr<Adjacent<T>> &next) : _key(std::move(key)), _next(std::move(next)) {};

};

}  // namespace lab4

#endif  // LAB_DS_LAB4_GRAPH_HH_
