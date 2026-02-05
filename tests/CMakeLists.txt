# Test executable
add_executable(gw-core-tests
        test_audio_format.cpp
        test_audio_buffer.cpp
        test_buffer_view.cpp
        test_ring_buffer.cpp
        test_main.cpp
)

# Link against our library
target_link_libraries(gw-core-tests
        PRIVATE gw::core
)

# Apply compiler warnings
set_project_warnings(gw-core-tests)