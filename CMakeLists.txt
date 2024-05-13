cmake_minimum_required(VERSION 3.20)
project(ccursor LANGUAGES C)

# Enable clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the ccursor library
add_library(ccursor 
    src/ccursor.c
)

# Set include directories
target_include_directories(ccursor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(ccursor PRIVATE -Wall -Wextra -Werror)

# Include tests
enable_testing()
add_subdirectory(tests)