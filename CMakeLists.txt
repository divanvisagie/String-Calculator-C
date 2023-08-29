cmake_minimum_required(VERSION 3.10)

project(MyProject)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Specify the directories where the source files are located
set(SOURCE_DIR "src")
set(TEST_DIR "tests")

# Define the executables
add_executable(main_app ${SOURCE_DIR}/main.cpp)
add_executable(test_app ${TEST_DIR}/test.cpp)

# Link Conan libraries
target_link_libraries(main_app ${CONAN_LIBS})
target_link_libraries(test_app ${CONAN_LIBS})

