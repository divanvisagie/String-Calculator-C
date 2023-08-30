# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(StringCalculator VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Locate the cmocka package
find_package(cmocka CONFIG REQUIRED)

# Include directories for main source code
include_directories(${CMAKE_SOURCE_DIR}/src)

# Main application target
add_executable(main_app src/main.c)

# Test application target
add_executable(test_app tests/test_main.c)
target_link_libraries(test_app cmocka::cmocka)

# Optionally, you can include a target to run the tests as part of the build process
add_custom_target(run_tests
    COMMAND test_app
    DEPENDS test_app
)

