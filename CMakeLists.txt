cmake_minimum_required(VERSION 3.13)
project(Gm3d)

add_library(cppid-gm3d INTERFACE)
add_library(cppid::gm3d ALIAS cppid-gm3d)

target_include_directories(cppid-gm3d
INTERFACE
  "${PROJECT_SOURCE_DIR}/src/"
)

target_compile_options(cppid-gm3d
  INTERFACE
    -Wall
    -Wpedantic
    -pedantic-errors
    -fno-rtti
)

target_compile_features(cppid-gm3d
  INTERFACE
    cxx_std_17
)

if(GM3D_BUILD_TESTING)
  enable_testing()

  add_subdirectory("third_party/Catch2")

  set(Gm3d_TEST_SRC_FILES
  "${PROJECT_SOURCE_DIR}/test/matrix3.cpp"
  "${PROJECT_SOURCE_DIR}/test/matrix4.cpp"
  "${PROJECT_SOURCE_DIR}/test/rgba_float.cpp"
  "${PROJECT_SOURCE_DIR}/test/rgba_uint8.cpp"
  "${PROJECT_SOURCE_DIR}/test/vector2.cpp"
  "${PROJECT_SOURCE_DIR}/test/vector3.cpp"
  )

  foreach(Gm3d_FILES ${Gm3d_TEST_SRC_FILES})

    get_filename_component(Gm3d_NAME ${Gm3d_FILES} NAME_WE)

    set(Gm3d_TARGET_NAME "cppid-gm3d-test-${Gm3d_NAME}")

    add_executable(${Gm3d_TARGET_NAME} ${Gm3d_FILES})

    target_link_libraries(${Gm3d_TARGET_NAME}
      PRIVATE
        cppid::gm3d
        Catch2::Catch2
    )

    add_test(
      NAME ${Gm3d_TARGET_NAME}
      COMMAND ${Gm3d_TARGET_NAME}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  endforeach()

endif()
