include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest)

add_executable(register_tests register_tests.cpp)

target_link_libraries(register_tests
    PRIVATE
    GTest::GTest
    register
)

add_test(NAME register_tests COMMAND register_tests)
