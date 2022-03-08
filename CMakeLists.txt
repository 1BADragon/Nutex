cmake_minimum_required(VERSION 3.15)
project(Nutex CXX)

add_library(nutex INTERFACE)
target_include_directories(nutex INTERFACE include)
target_sources(nutex INTERFACE
    include/nutex.hpp
    include/nutex/lock.hpp
    include/nutex/lockref.hpp
    include/nutex/spinlock.hpp
    )



option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
