cmake_minimum_required(VERSION 3.10)
project(SYSCLI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(sys-cli ${SRC})

if(MSVC)
    target_compile_options(sys-cli PRIVATE /W4 /permissive-)
else()
    target_compile_options(sys-cli PRIVATE -Wall -Wextra -Wpedantic)
endif()
