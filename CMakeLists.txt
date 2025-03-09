cmake_minimum_required(VERSION 3.26)

# ===================================================================================================
# Top-level project.
# ===================================================================================================
project(pulsar LANGUAGES CXX)

set(PULSAR_TEST_ENABLE ON)

# Use folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

# Configure C++ standard.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable export compile command.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(core)
add_subdirectory(runtime)
add_subdirectory(platform)
add_subdirectory(samples/01_demo)
add_subdirectory(samples/serializer_demo)


