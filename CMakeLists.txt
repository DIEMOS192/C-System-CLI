cmake_minimum_required(VERSION 3.10)
project(SYSCLI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SYS/include)

# Collect all .cpp sources under SYS/src (includes main.cpp and command implementations).
# Use CONFIGURE_DEPENDS so CMake will re-run if sources are added/removed during development.
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/SYS/src/*.cpp"
)

if(NOT SRC)
    message(FATAL_ERROR "No source files found under ${CMAKE_CURRENT_SOURCE_DIR}/SYS/src.\n"
                    "Make sure your .cpp files are in SYS/src/ (e.g. SYS/src/main.cpp, SYS/src/commands/...).")
endif()

add_executable(sys-cli ${SRC})

if(MSVC)
    target_compile_options(sys-cli PRIVATE /W4 /permissive-)
else()
    target_compile_options(sys-cli PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Provide a default version macro if not supplied by toolchain
target_compile_definitions(sys-cli PRIVATE SYSCLI_VERSION="0.2.0")
