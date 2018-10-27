cmake_minimum_required(VERSION 3.11)
project(Gm3d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Gm3d_WARNING_OPTIONS "-Wall" "-Wpedantic")

add_library(gm3d INTERFACE)

target_include_directories(gm3d
INTERFACE
  "${PROJECT_SOURCE_DIR}/third_party/GSL/include"
)

target_compile_options(gm3d INTERFACE ${Gm3d_WARNING_OPTIONS} "-stdlib=libc++")


