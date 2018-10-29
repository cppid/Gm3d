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


enable_testing()

set(Gm3d_TEST_SRC_FILES
"${PROJECT_SOURCE_DIR}/test/rgba_float.cpp"
"${PROJECT_SOURCE_DIR}/test/rgba_uint8.cpp"
"${PROJECT_SOURCE_DIR}/test/vector2.cpp"
"${PROJECT_SOURCE_DIR}/test/vector3.cpp"
)

foreach(Gm3d_FILES ${Gm3d_TEST_SRC_FILES})

  get_filename_component(Gm3d_NAME ${Gm3d_FILES} NAME_WE)

  set(Gm3d_TARGET_NAME "gm3d-test-${Gm3d_NAME}")

  add_executable(${Gm3d_TARGET_NAME} ${Gm3d_FILES})

  target_link_libraries(${Gm3d_TARGET_NAME} PRIVATE gm3d)

  target_include_directories(${Gm3d_TARGET_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/src/"
    "${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include"
  )

  target_compile_options(
    ${Gm3d_TARGET_NAME} PRIVATE ${Gm3d_WARNING_OPTIONS} "-stdlib=libc++")

  add_test(
    NAME ${Gm3d_TARGET_NAME}
    COMMAND ${Gm3d_TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

endforeach()


