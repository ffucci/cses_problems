cmake_minimum_required(VERSION 3.24.4)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER /opt/local/libexec/llvm-16/bin/clang++)
set(CMAKE_CXX_STANDARD 20)

project(cses_solutions)

add_subdirectory(array_description)
add_subdirectory(apple_division)
add_subdirectory(apartments)
add_subdirectory(book_shop)
add_subdirectory(dynamic_sum_queries)

add_subdirectory(edit_distance)
add_subdirectory(static_queries)
add_subdirectory(static_min_range_queries)
add_subdirectory(dynamic_min_range_queries)

add_subdirectory(range_xor)
add_subdirectory(range_update)

add_subdirectory(stick_lengths)
add_subdirectory(sum_values)
add_subdirectory(two_sets_2)
