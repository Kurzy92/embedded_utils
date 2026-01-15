add_library(register INTERFACE)

enable_testing()
add_subdirectory(tests)
target_include_directories(register INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
