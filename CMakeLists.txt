cmake_minimum_required(VERSION 3.15)
project(Nutex CXX)

add_library(nutex
    include/nutex.hpp
    include/nutex/lock.hpp
    include/nutex/rwlock.hpp
    include/nutex/lockref.hpp
    include/nutex/spinlock.hpp
    src/spinlock.cpp)
target_include_directories(nutex PUBLIC include)

option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
