cmake_minimum_required(VERSION 3.19)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
project("sdb" LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(libedit REQUIRED IMPORTED_TARGET libedit)

# Testing
include(CTest)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tools)

if (BUILD_TESTING)
    find_package(Catch2 CONFIG REQUIRED)
    add_subdirectory(test)
endif ()
