cmake_minimum_required(VERSION 3.15)
project(lab_ds CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(lab1 lab1/SeqList.h lab1/main.cpp)
#add_executable(lab2 lab2/LinkList.hh)
add_executable(lab3 lab3/BiNode.hh lab3/BiNode.cc lab3/BiTree.hh lab3/main.cc lab3/BiTree.cc utils/utils.hh lab3/compat.hh)