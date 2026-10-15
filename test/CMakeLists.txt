cmake_minimum_required(VERSION 3.22)

# Standalone host-side test project. Built with the host compiler, NOT the ARM toolchain.
project(NUCLEO-144-tests C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(unit_tests
    logging_test.cpp
        ../Application/edt_log_item_handler.c
    # Add test files and hardware-independent firmware sources here
)

target_include_directories(unit_tests PRIVATE
    ../Application
)

target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

gtest_discover_tests(unit_tests)
