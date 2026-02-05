# Define the library target
add_library(gw-core
        version.cpp
        audio_format.cpp
        audio_buffer.cpp
        buffer_view.cpp
        ring_buffer.cpp
)

# Create an alias for consistency
# Allows both add_subdirectory and find_package to work the same way
add_library(gw::core ALIAS gw-core)

# Set include directories
target_include_directories(gw-core
        PUBLIC
        # When building, users need the include/directory
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        # When installed, headers will be in a different location
        $<INSTALL_INTERFACE:include>
        PRIVATE
        # Private headers (if any) would go here
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Apply compiler warnings
set_project_warnings(gw-core)

# Set target properties
set_target_properties(gw-core PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)