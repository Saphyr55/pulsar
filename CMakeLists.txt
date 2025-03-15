cmake_minimum_required(VERSION 3.26)

# ===================================================================================================
# Top-level project.
# ===================================================================================================
project(pulsar LANGUAGES CXX)

option(PULSAR_TEST_ENABLE "Enable test." ON)

if(PULSAR_TEST_ENABLE)
    include(CTest)
    enable_testing()
endif()

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

find_package(Vulkan)

add_subdirectory(core)
add_subdirectory(runtime)
add_subdirectory(platform)
add_subdirectory(samples/01_demo)
add_subdirectory(third_party)
if (Vulkan_FOUND)
    add_subdirectory(modules/renderer-vulkan)
endif()

add_subdirectory(tests)
