cmake_minimum_required(VERSION 3.5)
project(ELEN3009_Game_SFML)
# On Windows recommended to set the SFML_ROOT environment variable to specify SFML sources.

# Define sources and executable
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "ELEN3009_Game_SFML")
set(LIBRARY_NAME "ELEN_Game_SFML_LIB")
set(TEST_EXECUTABLE_NAME "ELEN3009_Game_SFML_TESTS")

# Enable debug symbols by default
# must be done before project() statement
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

add_subdirectory(main)

enable_testing()
add_subdirectory(test)
