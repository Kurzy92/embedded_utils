cmake_minimum_required(VERSION 3.22)

# Define the register component as an interface library (header-only)
add_library(embedded_register INTERFACE)
add_library(embedded_utils::register ALIAS embedded_register)

# Set include directories
target_include_directories(embedded_register INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Require C++20
target_compile_features(embedded_register INTERFACE cxx_std_20)

# Add tests if this is the main project or if explicitly requested
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR OR EMBEDDED_UTILS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation rules
install(TARGETS embedded_register
    EXPORT embedded_register-targets
    INCLUDES DESTINATION include
)

install(FILES register.hpp
    DESTINATION include/embedded_utils
)

install(EXPORT embedded_register-targets
    FILE embedded_register-targets.cmake
    NAMESPACE embedded_utils::
    DESTINATION lib/cmake/embedded_register
)

# Create and install config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/embedded_register-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/embedded_register-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/embedded_register-config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/embedded_register-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/embedded_register-config-version.cmake"
    DESTINATION lib/cmake/embedded_register
)
