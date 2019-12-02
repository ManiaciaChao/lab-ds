//
// Created by user24 on 2019/11/27.
//

#pragma once
#ifndef LAB_DS_UTILS_UTILS_HH_
#define LAB_DS_UTILS_UTILS_HH_
#include <cstring>
#include <sys/ioctl.h>
#include <iostream>
#include <iomanip>
#include <itclInt.h>
#include <bits/stdc++.h>
#ifdef _WIN32
include "conio.h"
#endif

#define ERR_HINT "Invalid input, please re-input:"
#define POSIX_CLS "\033[2J\033[1;1H"

namespace utils {

auto consoleWidth()->size_t {
  size_t consoleWidth;
  // get console width
#ifdef WIN32
  CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    consoleWidth = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
#else
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  consoleWidth = w.ws_col;
#endif
  return consoleWidth;
}

template<typename T>
auto scan(T &var, const bool line = false) {
  std::cin >> var;
}

auto scan(std::string &var, const bool line = false) {
  if (line) {
    std::getline(std::cin, var);
  } else {
    std::cin >> var;
  }
}

// accept input and validation
template<typename T, bool line = false>
auto scanHelper(T &var,
                std::function<bool(T &)> compare,
                const std::string &hint = "",
                const std::string &err = ERR_HINT) -> void {
  if (!hint.empty()) {
    std::cout << hint << " ";
  }
  scan(var, line);
  while (!compare(var)) {
    std::cout << err << " ";
    scan(var, line);
  }
}

template<typename T, bool line = false>
inline auto scanHelper(T &var,
                       const std::string &hint = "",
                       const std::string &err = ERR_HINT) -> void {
  scanHelper<T, line>(var, [](T &var) { return true; }, hint, err);
}

// clear screen
auto clear() -> void {
#ifdef _WIN32
  clrscr();
#else
  std::cout << POSIX_CLS;
#endif
}

// print horizontal lines
auto hr(char placeHolder = '-') -> void {
  for (size_t i = 0; i < consoleWidth(); i++) { std::cout << placeHolder; }
  std::cout << std::endl;
}

template<typename T>
int printHelper(lab3::BiNode<T> *node, bool isLeft, int offset, int depth, char **buffer) {
  char b[20] = "";
  if (!node) {
    return 0;
  }
  auto key = node->key();
  int digits = key.length();
  int width = 2 + digits;
  // insert to buffer
  sprintf(b, "(%s)", key.c_str());

  // width of left child
  int left = printHelper(node->left(), true, offset, depth + 1, buffer);
  // width of right child
  int right = printHelper(node->right(), false, offset + left + width, depth + 1, buffer);

  // element on root, which is in even row of `buffer`
  for (int i = 0; i < width; i++) {
    buffer[2 * depth][offset + left + i] = b[i];
  }

  // connection line
  if (depth) { // not root
    buffer[2 * depth - 1][offset + left + width / 2] = '+';
    if (isLeft) { // is left child
      for (int i = 1; i < width + right; i++)
        buffer[2 * depth - 1][offset + left + width / 2 + i] = '-';
      // get parent position
      buffer[2 * depth - 1][offset + left + width + right + width / 2] = '+';
    } else { // is right child
      for (int i = 0; i < left + width - 1; i++)
        buffer[2 * depth - 1][offset - width / 2 + i] = '-';
      // get parent position
      buffer[2 * depth - 1][offset - width / 2 - 1] = '+';
    }
  }

  return left + width + right;
}

/**
 * Print tree beautifully
 * @param {BinaryTree *} binaryTree - binaryTree
 * @param {int} height - height of tree
 * @param {int} width - width of console
 * @return {Status} - execution status
 */
template<typename T>
bool beautifulPrinter(lab3::BiTree<T> *tree, int height, int width) {
  // initialize buffer
  char **s = static_cast<char **>(malloc(sizeof(char *) * height));
  for (int i = 0; i < height; i++) {
    s[i] = static_cast<char *>(malloc(sizeof(char) * width));
    memset(s[i], ' ', sizeof(char) * width);
    s[i][width - 1] = '\0';
  }

  int finalWidth = printHelper(tree->root(), false, 0, 0, s);
  if (finalWidth > width) { // width exceeds
    printf("[WARNING: The width of console CANNOT show the whole tree!]\n");
    return false;
  }

  for (int i = 0; i < height; i++) { // print items from buffer
    printf("%s\n", s[i]);
    free(s[i]); // free buffer item
  }
  free(s); // free buffer
  return true;
}

/**
 * Print tree
 * @param {BinaryTree *} binaryTree - binaryTree
 * @return {Status} - execution status
 */
template<typename T>
bool print(lab3::BiTree<T> *tree) {
  if (tree->root()== nullptr) { // tree doesn't exist
    return false;
  }
  size_t consoleWidth= utils::consoleWidth();
  int height = 2 * tree->depth() - 1;
  for (size_t i = 0; i < consoleWidth; i++) {
    printf("-");
  }
  printf("\n");

  auto status = beautifulPrinter(tree, height, consoleWidth);
  if (!status) {
    return false;
  }
  for (int i = 0; i < consoleWidth; i++) {
    printf("-");
  }
  printf("\n");
  return true;
}

}

#endif //LAB_DS_UTILS_UTILS_HH_
