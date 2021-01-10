cmake_minimum_required(VERSION 3.0)
project(lexgram C CXX)

add_subdirectory(lexgram)

enable_testing()
add_subdirectory(tests)
