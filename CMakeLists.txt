cmake_minimum_required(VERSION 3.7)
project (AVLTree)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(AVLTree)

set(SOURCE_FILES main.cpp)
add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main LINK_PUBLIC avltree)

# Configuration for tests
