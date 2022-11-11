cmake_minimum_required(VERSION 3.5)
project(regression)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Eigen
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories ( "${EIGEN3_INCLUDE_DIR}")


add_executable(main src/main.cpp)
