cmake_minimum_required(VERSION 3.15...3.30)

project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/common/glad/glad.c")
target_include_directories(glad PUBLIC common common/glad)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/glfw3.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include"
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/common/shader
)

add_subdirectory(01_House)
add_subdirectory(02_Shaders)
add_subdirectory(03_Textures)
