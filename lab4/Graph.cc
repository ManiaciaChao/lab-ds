//
// Created by user24 on 2019/12/11.
//
#include "Graph.hh"
#include <fstream>
#include <sstream>

namespace lab4 {

template<typename T>
void Vertex<T>::traverse(callback cb) const {
  auto node = _next.get();
  int a = 1;
  while (node != nullptr) {
    if (!cb(*node)) {
      break;
    }
    node = node->_next.get();
  }
}

template<typename T>
bool Vertex<T>::has(Key key) {
  auto res = false;
  traverse([&key, &res](Adjacent<T> &adj) {
    if (adj._key == key) {
      res = true;
      return false;
    }
    return true;
  });
  return res;
}

template<typename T>
Graph<T>::Graph(std::vector<Vertex<T>> &vertices) {
  for (Vertex<T> &vertex:vertices) {
    insert(vertex);
  }
}

template<typename T>
Graph<T>::Graph(std::vector<Vertex<T>> &vertices, std::vector<ArcPair> &arcs) {
  for (Vertex<T> &vertex:vertices) {
    insert(vertex);
  }
  for (ArcPair &arc:arcs) {
    link(arc.from, arc.to);
  }
}

template<typename T>
inline Vertex<T> &Graph<T>::locate(const Key &key) {
  return _nodes.at(key);
}

template<typename T>
void Graph<T>::assign(const Key &key, T val) {
  auto &vex = locate(key);
  vex._val = val;
}

template<typename T>
Vertex<T> &Graph<T>::firstAdj(const Key &key) {
  auto &vex = locate(key);
  auto next = vex._next.get();
  return locate(next->_key);
}

template<typename T>
Vertex<T> &Graph<T>::nextAdj(const lab4::Key &key, const lab4::Key &after) {
  auto &vex = locate(key);
  auto next = vex._next.get();
  while (next->_key != after) {
    next = next->_next.get();
  }
  return locate(next->_key);
}

template<typename T>
void Graph<T>::insert(Vertex<T> &vertex) {
  _nodes.insert({vertex.key(), vertex});
}

template<typename T>
void Graph<T>::remove(const lab4::Key &key) {
  _nodes.erase(key);
  for (const auto &pair : _nodes) {
    unlink(pair.first, key);
  }
}

template<typename T>
void Graph<T>::link(const lab4::Key &from, const lab4::Key &to) {
  auto &nodeFrom = locate(from);
//auto &nodeFrom = _nodes.at(from);
  if (_nodes.find(to) == _nodes.end()) {
    throw std::runtime_error("Not found");
  }
  if (nodeFrom.has(to)) {
    return;
  }
  auto a = std::make_unique<Adjacent<T>>(to, nodeFrom._next);
  nodeFrom._next = std::move(a);
}

template<typename T>
void Graph<T>::unlink(const lab4::Key &from, const lab4::Key &to) {
  auto &vex = locate(from);
  auto cur = vex._next.get();
  auto prev = cur;
  while (cur != nullptr) {
    if (cur->_key == to) {
      if (prev->_key == to) {
        vex._next = std::move(cur->_next);
      } else {
        prev->_next = std::move(cur->_next);
      }
    }
    prev = cur;
    cur = cur->_next.get();
  }
}
template<typename T>
void Graph<T>::dfs(callback cb) {
  auto visited = std::set<std::string>{};
  auto stack = std::stack<Key>();
  for (const auto &pair: _nodes) {
    if (visited.find(pair.first) == visited.end()) {
      stack.push(pair.first);
      visited.insert(pair.first);
    }
    while (!stack.empty()) {
      auto curKey = std::move(stack.top());
      stack.pop();
      cb(locate(curKey));
      locate(curKey).traverse([&stack, &visited](Adjacent<T> &adj) {
        if (visited.find(adj._key) == visited.end()) {
          stack.push(adj._key);
          visited.insert(adj._key);
        }
        return true;
      });
    }
  }
}
template<typename T>
void Graph<T>::bfs(callback cb) {
  auto visited = std::set<std::string>{};
  auto queue = std::queue<Key>();
  for (const auto &pair: _nodes) {
    if (visited.find(pair.first) == visited.end()) {
      queue.push(pair.first);
      visited.insert(pair.first);
    }
    while (!queue.empty()) {
      auto curKey = std::move(queue.front());
      queue.pop();
      cb(locate(curKey));
      locate(curKey).traverse([&queue, &visited](Adjacent<T> &adj) {
        if (visited.find(adj._key) == visited.end()) {
          queue.push(adj._key);
          visited.insert(adj._key);
        }
        return true;
      });
    }
  }
}

template<typename T>
void Graph<T>::save(const std::string &filename) {
  std::ofstream f;
  f.open(filename);
  for (const auto &pair: _nodes) {
    f << pair.first << separator.Val << pair.second._val;
    auto &vex = pair.second;
    if (vex._next.get() != nullptr) {
      f << separator.Link;
      vex.traverse([&f, this](Adjacent<T> &arc) {
        f << arc._key;
        if (arc._next.get() != nullptr) {
          f << separator.And;
        }
        return true;
      });
    }
    f << std::endl;
  }
  f.close();
}

template<typename T>
void Graph<T>::load(std::basic_istream<char> &stream) {
  std::string line, key, str_val;
  T val = 0;
  std::vector<Vertex<T>> vertices;
  std::vector<ArcPair> arcs;
  while (!stream.eof()) {
    std::getline(stream, line); // read 1 line into string
    if (line.length() == 0) {
      break;
    }
    auto buf = std::istringstream(line); // convert string to stream
    std::getline(buf, key, separator.Val); // read string before ':' as key
    std::getline(buf, str_val, separator.Link); // read string before '&' as val
    auto buf_val = std::istringstream(str_val);
    buf_val >> val;
    vertices.push_back(Vertex<T>{key, val});

    while (!buf.eof()) {
      std::string to;
      std::getline(buf, to, separator.And);
      arcs.push_back(ArcPair{key, to});
    }
  }
  *this = Graph<T>{vertices, arcs};
}
template<typename T>
void Graph<T>::load(const std::string &filename) {
  std::ifstream f;
  f.open(filename);
  load(f);
  f.close();
}
}  // namespace lab4
