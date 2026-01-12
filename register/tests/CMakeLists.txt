cmake_minimum_required(VERSION 3.22)

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Enable testing
enable_testing()

# Create test executable
add_executable(register_tests
    test_register.cpp
)

# Link against the register library and Catch2
target_link_libraries(register_tests
    PRIVATE
        embedded_register
        Catch2::Catch2WithMain
)

# Add tests to CTest
include(CTest)
include(Catch)
catch_discover_tests(register_tests)
