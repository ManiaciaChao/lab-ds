//
// Created by user24 on 2019/12/9.
//

#include <iostream>
//#include "Graph.cc"
#include "compat.hh"
#include "utils/utils.hh"

using ElemType = int;
using namespace lab4;
const int EXIT = 20;

int test() {
  std::vector<lab4::Vertex<ElemType>> vertices = {
      Vertex<ElemType>("B", 2),
      Vertex<ElemType>("E", 5),

      Vertex<ElemType>("A", 1),
      Vertex<ElemType>("C", 3),
      Vertex<ElemType>("D", 4),
  };
  std::vector<lab4::ArcPair> arcs = {
      ArcPair{"A", "B"},
      ArcPair{"A", "C"},

      ArcPair{"B", "D"},
      ArcPair{"B", "E"},

  };
  for (auto vertex :vertices) {
    std::cout << vertex.key() << " ";
  }
  std::cout << std::endl;

  Graph<ElemType> a = {vertices, arcs};
  a.dfs([](Vertex<ElemType> &node) {
    std::cout << node.key() << " ";
    return true;
  });
  std::cout << std::endl;
  a.remove("E");
  a.bfs([](Vertex<ElemType> &node) {
    std::cout << node.key() << " ";
    return true;
  });
  std::cout << std::endl;
  a.save("aaa.sav");

  Graph<ElemType> b;
  b.load("aaa.sav");
  b.dfs([](Vertex<ElemType> &node) {
    std::cout << node.key() << " ";
    return true;
  });
  std::cout << std::endl;
  return 1;
}

bool traverse(Vertex<ElemType> &vex) {
  printf("%-10s%-5s", vex.key().c_str(), "Adj:");
  vex.traverse([](Adjacent<ElemType> &arc) {
    std::cout << arc._key << " ";
    return true;
  });
  std::cout << std::endl;
  return true;
}

template<typename T, int N>
void displayMenu(std::array<lab4::Graph<T> *, N> forest, int index = 0) {
  utils::hr();
  printf("Current Index : %d \n", index);
  if (forest[index] == nullptr) {
    printf("%-20s%-20s\n", "1. InitGraph", "19. Switch");
  } else {
    printf("%-20s%-20s\n", "1. InitGraph", "19. Switch");
    printf("%-20s%-20s\n", "2. DestroyGraph", "3. CreateGraph");
    printf("%-20s%-20s\n", "4. LocateVex", "5. PutVex");
    printf("%-20s%-20s\n", "6. FirstAdjVex", "7. NextAdjVex");
    printf("%-20s%-20s\n", "8. InsertVex", "9. DeleteVex");
    printf("%-20s%-20s\n", "10. InsertArc", "11. RemoveArc");
    printf("%-20s%-20s\n", "12. DFSTraverse", "13. BFSTraverse");
    printf("%-20s%-20s\n", "14. SaveFile", "15. LoadFile");
  }
}

int main() {
  utils::clear();
  auto graph_array = std::array<lab4::Graph<ElemType> *, 20>();
  int option = 0;
  int graph_index = 0;
  while (option != EXIT) {
    try {
      option = 0;
      displayMenu<ElemType, 20>(graph_array, graph_index);
      utils::scanHelper<ElemType>(option, [&](ElemType &var) {
        return ((graph_array[graph_index] != nullptr && var > 0 && var <= 25)
            || (graph_array[graph_index] == nullptr && (var == 1 || var == 19)));
      }, "Choose an option:", "Invalid option, please re-input:");
      getchar();
      utils::hr();
      switch (option) {
        case 1: {
          std::cout << "InitGraph" << std::endl;
          compat::InitGraph(graph_array[graph_index]);
          std::cout << "Graph " << graph_index << " inited!" << std::endl;
          break;
        }
        case 2: {
          std::cout << "DestroyGraph" << std::endl;
          compat::DestroyGraph(graph_array[graph_index]);
          std::cout << "Graph " << graph_index << " destroyed!" << std::endl;
          break;
        }
        case 3: {
          std::cout << "CreateGraph" << std::endl;
//          getchar();
          std::string str;
          std::getline(std::cin, str, '^');
          std::istringstream str_buf{str};
          graph_array[graph_index]->load(str_buf);
          break;
        }
        case 4: {
          std::cout << "LocateVex" << std::endl;
          std::string key;
          utils::scanHelper<std::string, true>(key, "Input vertex's key:");
          auto vertex = compat::LocateVex(graph_array[graph_index], key);
          if (vertex) {
            std::cout << "Vertex found: { _key: \"" << vertex->key() << "\", val: \"" << vertex->val() << "\" }"
                      << std::endl;
          } else {
            std::cout << "Vertex not found!" << std::endl;
          }
          break;
        }
        case 5: {
          std::cout << "PutVex" << std::endl;
          std::string key;
          ElemType val = 0;
          utils::scanHelper<std::string, true>(key, "Input vertex's key:");
          utils::scanHelper<ElemType>(val, "Input node's val:");
          auto res = compat::PutVex(graph_array[graph_index], key, val);
          if (res) {
            std::cout << "Vertex found: { _key: \"" << key << "\", val: \"" << val << "\" }" << std::endl;
          } else {
            std::cout << "Vertex not found!" << std::endl;
          }
          break;
        }
        case 6: {
          std::cout << "FirstAdjVex" << std::endl;
          std::string key;
          utils::scanHelper<std::string, true>(key, "Input vertex's key:");
          auto vertex = compat::FirstAdjVex(graph_array[graph_index], key);
          if (vertex) {
            std::cout << "Vertex found: { _key: \"" << vertex->key() << "\", val: \"" << vertex->val() << "\" }"
                      << std::endl;
          } else {
            std::cout << "Vertex not found!" << std::endl;
          }
          break;
        }
        case 7: {
          std::cout << "NextAdjVex" << std::endl;
          std::string key, after;
          utils::scanHelper<std::string, true>(key, "Input vertex's key:");
          utils::scanHelper<std::string, true>(after, "After key:");
          auto vertex = compat::NextAdjVex(graph_array[graph_index], key, after);
          if (vertex) {
            std::cout << "Vertex found: { _key: \"" << vertex->key() << "\", val: \"" << vertex->val() << "\" }"
                      << std::endl;
          } else {
            std::cout << "Vertex not found!" << std::endl;
          }
          break;
        }
        case 8: {
          std::cout << "InsertVex" << std::endl;
          std::string key;
          ElemType val = 0;
          utils::scanHelper<std::string, true>(key, "Input new vertex's key:");
          utils::scanHelper<ElemType>(val, "Input new node's val:");
          auto res = compat::InsertVex(graph_array[graph_index], new Vertex<ElemType>{key, val});
          break;
        }
        case 9: {
          std::cout << "DeleteVex" << std::endl;
          std::string key;
          utils::scanHelper<std::string, true>(key, "Input vertex's key:");
          compat::DeleteVex(graph_array[graph_index], key);
          break;
        }
        case 10: {
          std::cout << "InsertArc" << std::endl;
          std::string from, to;
          utils::scanHelper<std::string, true>(from, "Input from vertex's key:");
          utils::scanHelper<std::string, true>(to, "Input to vertex's key:");
          auto res = compat::InsertArc(graph_array[graph_index], from, to);
          break;
        }
        case 11: {
          std::cout << "DeleteArc" << std::endl;
          std::string from, to;
          utils::scanHelper<std::string, true>(from, "Input from vertex's key:");
          utils::scanHelper<std::string, true>(to, "Input to vertex's key:");
          auto res = compat::DeleteArc(graph_array[graph_index], from, to);
          break;
        }
        case 12: {
          std::cout << "DFSTraverse" << std::endl;
          compat::DFSTraverse(graph_array[graph_index], traverse);
          break;
        }
        case 13: {
          std::cout << "BFSTraverse" << std::endl;
          compat::BFSTraverse(graph_array[graph_index], traverse);
          break;
        }
        case 14: {
          std::cout << "SaveFile" << std::endl;
          std::string filename;
          utils::scanHelper<std::string, true>(filename, "Save as (default is graph_{index}.sav):");
          if (filename.empty()) {
            filename = "graph_" + std::to_string(graph_index) + ".sav";
          }
          graph_array[graph_index]->save(filename);
          break;
        }
        case 15: {
          std::cout << "LoadFile" << std::endl;
          std::string filename;
          utils::scanHelper<std::string, true>(filename, "Load from (default is graph_{index}.sav):");
          if (filename.empty()) {
            filename = "graph_" + std::to_string(graph_index) + ".sav";
          }
          graph_array[graph_index]->load(filename);
          break;
        }
        case 19: {
          std::cout << "Switch" << std::endl;
          utils::scanHelper<int>(graph_index,
                                 [graph_index](int index) { return index < 20 && index >= 0; },
                                 "Switch to graph:");
          break;
        }
        default:break;
      }
    } catch (std::exception &e) {
      std::cout << std::endl;
      utils::hr('+');
      std::cout << "RuntimeException: " << std::endl << e.what() << std::endl;
      utils::hr('+');
      std::cout << std::endl;
    }
  }
  return 1;
}