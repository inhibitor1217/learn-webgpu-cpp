cmake_minimum_required(VERSION 3.5.0)
project(learn-webgpu-cpp VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(COMPILE_WARNING_AS_ERROR ON)

add_executable(learn-webgpu-cpp
    src/main.cpp
    src/Engine.cpp)

if (MSVC)
    target_compile_options(learn-webgpu-cpp PRIVATE /W4)
else()
    target_compile_options(learn-webgpu-cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(DAWN_FETCH_DEPENDENCIES ON)
add_subdirectory("dawn" EXCLUDE_FROM_ALL)
target_link_libraries(learn-webgpu-cpp PRIVATE dawn::webgpu_dawn glfw webgpu_glfw)
