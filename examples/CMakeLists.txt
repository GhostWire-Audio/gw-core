# Simple example executable
add_executable(hello_ghostwire
        hello_ghostwire.cpp
)

# Link against our library
target_link_libraries(hello_ghostwire
        PRIVATE gw::core
)

# Apply warnings to examples too
set_project_warnings(hello_ghostwire)