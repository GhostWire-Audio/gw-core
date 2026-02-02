# Minimum CMake version supported
cmake_minimum_required(VERSION 3.15)

# Project declaration
project(GhostWireCore
    VERSION 0.1.0
    DESCRIPTION "Real-time audio DSP engine"
    LANGUAGES CXX
)

# Allows gw-core to be used as a sub-project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Use C++17
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Enable folder organization in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Export compile commands for tools like clangd
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Include our custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include compiler warnings configuration
include(CompilerWarnings)

# Add subdirectories
#add_subdirectory(src)
#add_subdirectory(examples)