cmake_minimum_required(VERSION 3.9)
project(piMultiThread C)

set(CMAKE_C_STANDARD 99)

link_libraries(-lm)

link_libraries(pthread)


add_executable(piMultiThread main.c)