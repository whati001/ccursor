cmake_minimum_required(VERSION 3.20)
project(ccurser LANGUAGES C)

# Enable clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the ccurser library
add_library(ccurser 
    src/ccurser.c
)

# Set include directories
target_include_directories(ccurser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(ccurser PRIVATE -Wall -Wextra -Wpedantic -Werror -g)

# Include tests
enable_testing()
add_subdirectory(tests)