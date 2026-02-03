# This function adds strong compiler warnings to a target
function(set_project_warnings target_name)
    set(MSVC_WARNINGS
            /W4          # High warning level
            /w14640      # Warn on thread-unsafe static initialization
            /permissive- # Standards conformance mode
    )

    set(CLANG_WARNINGS
            -Wall        # Enable most warnings
            -Wextra      # Enable extra warnings
            -Wpedantic   # Warn on non-standard C++
            -Wshadow     # Warn when variables shadow each other
            -Wnon-virtual-dtor  # Warn on missing virtual destructors
            -Wcast-align        # Warn on dangerous casts
            -Wunused            # Warn on unused code
            -Woverloaded-virtual # Warn on overloaded virtuals
            -Wconversion        # Warn on type conversions that may lose data
            -Wsign-conversion   # Warn on sign conversions
            -Wformat=2          # Warn on printf format issues
    )

    set(GCC_WARNINGS
            ${CLANG_WARNINGS}
    )

    # Apply the appropriate warnings based on compiler
    if (MSVC)
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
    elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    else ()
        message(WARNING "Unknown compiler, no warnings set")
    endif ()

    target_compile_options(${target_name} PRIVATE ${PROJECT_WARNINGS})
endfunction()