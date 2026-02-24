cmake_minimum_required(VERSION 3.16)
project(thread_pool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(thread_pool
    src/ThreadPool.cpp
)

target_include_directories(thread_pool
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_executable(example
    examples/example.cpp
)

target_link_libraries(example
    PRIVATE thread_pool
)
