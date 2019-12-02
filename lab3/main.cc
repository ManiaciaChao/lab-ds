//
// Created by user24 on 2019/11/14.
//

//#include "BiNode.cc"
//#include "BiTree.cc"
#include "compat.hh"
#include "utils/utils.hh"

using ElemType = int;
using KVP = lab3::StringKeyValuePair<ElemType>;
const int EXIT = 20;

template<typename T, int N>
void displayMenu(std::array<lab3::BiTree<T> *, N> forest, int index = 0) {
  utils::hr();
  printf("Current Index : %d \n", index);
  if (forest[index] == nullptr) {
    printf("%-20s%-20s\n", "1. Init", "19. Switch");
  } else {
    printf("%-20s%-20s\n", "1. Init", "2. Destroy");
    printf("%-20s%-20s\n", "3. Create", "4. Clear");
    printf("%-20s%-20s\n", "5. Empty", "6. Depth");
    printf("%-20s%-20s\n", "7. Locate", "8. Assign");
    printf("%-20s%-20s\n", "9. Sibling", "10. Print");
    printf("%-20s%-20s\n", "11. Insert", "12. Delete");
    printf("%-20s%-20s\n", "13. PreOrder", "14. InOrder");
    printf("%-20s%-20s\n", "15. PostOrder", "16. LevelOrder");
    printf("%-20s%-20s\n", "17. Load", "18. Save");
    printf("%-20s%-20s\n", "19. Switch", "20. Exit");
  }
}

int main() {
  utils::clear();
  auto forest = std::array<lab3::BiTree<ElemType> *, 20>();
  int option = 0;
  int treeIndex = 0;
  while (option != EXIT) {
    try {
      option = 0;
      displayMenu<ElemType, 20>(forest, treeIndex);
      utils::scanHelper<ElemType>(option, [&](ElemType &var) {
        return ((forest[treeIndex] != nullptr && var > 0 && var <= 20)
            || (forest[treeIndex] == nullptr && (var == 1 || var == 19)));
      }, "Choose an option:", "Invalid option, please re-input:");
      getchar();
      utils::hr();
      switch (option) {
        case 1: {
          std::cout << "Init" << std::endl;
          compat::InitBiTree(forest[treeIndex]);
          std::cout << "BiTree " << treeIndex << " inited!" << std::endl;
          break;
        }
        case 2: {
          std::cout << "Destroy" << std::endl;
          compat::DestroyBiTree(forest[treeIndex]);
          std::cout << "BiTree " << treeIndex << " destroyed!" << std::endl;
          break;
        }
        case 3: {
          std::cout << "Create" << std::endl;
          size_t len;
          utils::scanHelper<size_t>(len, [&](size_t len) {
            return len >= 0;
          }, "Input length of extended pre-order traverse list:");
//          getchar();
          std::vector<KVP> kvPairs;
          for (size_t i = 0; i < len; i++) {
            std::string key;
            ElemType val = 0;
            utils::scanHelper<std::string, true>(key, "Input node's key (Return for empty node):");
            if (!key.empty()) {
              utils::scanHelper<ElemType>(val, "Input node's value:");
              getchar();
              kvPairs.push_back(KVP{key, val});
            } else {
              kvPairs.push_back(KVP{"", val});
            }
          }
          compat::CreateBiTree(forest[treeIndex], kvPairs);
          break;
        }
        case 4: {
          std::cout << "Clear" << std::endl;
          compat::ClearBiTree(forest[treeIndex]);
          break;
        }
        case 5: {
          std::cout << "Empty" << std::endl;
          std::string empty = compat::BiTreeEmpty(forest[treeIndex]) ? "empty" : "not empty";
          std::cout << "BiTree " << treeIndex << " is " << empty << std::endl;
          break;
        }
        case 6: {
          std::cout << "Depth" << std::endl;
          auto depth = compat::BiTreeDepth(forest[treeIndex]);
          std::cout << "BiTree " << treeIndex << "'s depth is " << depth << std::endl;
          break;
        }
        case 7: {
          std::cout << "Locate" << std::endl;
          std::string key;
//          getchar();
          utils::scanHelper<std::string, true>(key, "Input node's key:");

          auto node = compat::LocateNode(forest[treeIndex], key);
//        auto node = forest[treeIndex]->locate(key);
          if (node) {
            std::cout << "Node found: { key: \"" << node->key() << "\", val: \"" << node->val() << "\" }" << std::endl;
          } else {
            std::cout << "Node not found!" << std::endl;
          }
          break;
        }
        case 8: {
          std::cout << "Assign" << std::endl;
          std::string key;
          ElemType val = 0;
          utils::scanHelper<std::string, true>(key, "Input node's key:");
          utils::scanHelper<ElemType>(val, "Input node's val:");
          auto res = compat::Assign(forest[treeIndex], key, val);
          if (res) {
            std::cout << "Node assigned: { key: \"" << key << "\", val: \"" << val << "\" }" << std::endl;
          } else {
            std::cout << "Node not found!" << std::endl;
          }
          break;
        }
        case 9: {
          std::cout << "Sibling" << std::endl;
          std::string key;
          utils::scanHelper<std::string, true>(key, "Input node's key:");
          auto node = compat::GetSibling(forest[treeIndex], key);
          if (node) {
            std::cout << "Node found: { key: \"" << node->key() << "\", val: \"" << node->val() << "\" }" << std::endl;
          } else {
            std::cout << "Node not found!" << std::endl;
          }
          break;
        }
        case 10: {
          std::cout << "Print" << std::endl;
          utils::print(forest[treeIndex]);
          break;
        }
        case 11: {
          std::cout << "Insert" << std::endl;
          std::string key;
          char posChar;
          utils::scanHelper<std::string, true>(key, "Input node's key:");
          utils::scanHelper<char>(posChar, [&](char posChar) {
            return posChar == 'L' || posChar == 'R';
          }, "Input position to insert (L for Left, R for Right):", "Invalid position, please re-input:");
          auto pos = posChar == 'L' ? lab3::Pos::Left : lab3::Pos::Right;
          getchar();
          std::string newKey;
          ElemType newVal = 0;
          utils::scanHelper<std::string, true>(newKey, "Input new node's key:");
          utils::scanHelper<ElemType, true>(newVal, "Input new node's val:");
          getchar();
          compat::InsertNode(forest[treeIndex], key, pos, new lab3::BiNode<ElemType>(newKey, newVal));
          break;
        }
        case 12: {
          std::cout << "Delete" << std::endl;
          std::string key;
          utils::scanHelper<std::string, true>(key, "Input node's key:");
//          compat::DeleteNode(forest[treeIndex],key);
          forest[treeIndex]->remove(key);
          break;

        }
        case 13: {
          std::cout << "PreOrder" << std::endl;
          forest[treeIndex]->preOrder([](lab3::BiNode<ElemType> &node) {
            std::cout << node.key() << ":" << node.val() << ";" << std::endl;
            return true;
          });
          break;
        }
        case 14: {
          std::cout << "InOrder" << std::endl;
          forest[treeIndex]->inOrder([](lab3::BiNode<ElemType> &node) {
            std::cout << node.key() << ":" << node.val() << ";" << std::endl;
            return true;
          });
          break;
        }
        case 15: {
          std::cout << "PostOrder" << std::endl;
          forest[treeIndex]->postOrder([](lab3::BiNode<ElemType> &node) {
            std::cout << node.key() << ":" << node.val() << ";" << std::endl;
            return true;
          });
          break;
        }
        case 16: {
          std::cout << "LevelOrder" << std::endl;
          forest[treeIndex]->levelOrder([](lab3::BiNode<ElemType> &node) {
            std::cout << node.key() << ":" << node.val() << ";" << std::endl;
            return true;
          });
          break;
        }
        case 17: {
          std::cout << "Load" << std::endl;
          std::string filename;
//          getchar();
          utils::scanHelper<std::string, true>(filename, "Load from (default is tree_{index}.sav):");
          if (filename.empty()) {
            filename = "tree_" + std::to_string(treeIndex) + ".sav";
          }
          forest[treeIndex]->load(filename);
          break;
        }
        case 18: {
          std::cout << "Save" << std::endl;
          std::string filename;
//          getchar();
          utils::scanHelper<std::string, true>(filename, "Save as (default is tree_{index}.sav):");
          if (filename.empty()) {
            filename = "tree_" + std::to_string(treeIndex) + ".sav";
          }
          forest[treeIndex]->save(filename);
          break;
        }
        case 19: {
          std::cout << "Switch" << std::endl;
          utils::scanHelper<int>(treeIndex,
                                 [treeIndex](int index) { return index < 20 && index >= 0; },
                                 "Switch to tree:");
          break;
        }
        case 20: {
          exit(1);
        }
        default: {
          break;
        }
      }
    } catch (std::exception &e) {
      std::cout << std::endl;
      utils::hr('+');
      std::cout << "RuntimeException: " << std::endl << e.what() << std::endl;
      utils::hr('+');
      std::cout << std::endl;
    }
  }
};