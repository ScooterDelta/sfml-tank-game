cmake_minimum_required(VERSION 2.4)
project(ELEN3009_Game_SFML)
# On Windows recommended to set the SFML_ROOT environment variable to specify SFML sources.

# Define sources and executable
set(EXECUTABLE_NAME "ELEN3009_Game_SFML")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES
        src/Angle.cpp
        src/Angle.h
        src/AxisAligned.h
        src/Battle.cpp
        src/Battle.h
        src/Display.cpp
        src/Display.h
        src/DrawableObject.h
        src/Explosion.cpp
        src/Explosion.h
        src/Gameplay.h
        src/HUD.cpp
        src/HUD.h
        src/main.cpp
        src/Mine.cpp
        src/Mine.h
        src/Missile.cpp
        src/Missile.h
        src/nonAxisAligned.h
        src/Obstacle.cpp
        src/Obstacle.h
        src/Score.cpp
        src/Score.h
        src/Tank.cpp
        src/Tank.h
        src/Turret.cpp
        src/Turret.h
        src/Vector2D.cpp
        src/Vector2D.h)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

# Enable debug symbols by default
# must be done before project() statement
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Check SFML Root Variable
if (EXISTS ${SFML_ROOT})
    # Check if SFML_ROOT is Set
    set(SFML_ROOT_DIR "${SFML_ROOT}")
else ()
    # Otherwise assign to environment
    set(SFML_ROOT_DIR "$ENV{SFML_ROOT}")
endif ()
# Copy SFML Dll's to target output directory.
# Only done on Windows if the SFML Root Dir variable is defined
if (WIN32)
    if (IS_DIRECTORY ${SFML_ROOT_DIR})
        file(GLOB SFML_LINK_DLLS "${SFML_ROOT_DIR}/lib/*.dll")
        foreach (SFML_LINK_DLL ${SFML_LINK_DLLS})
            add_custom_command(TARGET ${EXECUTABLE_NAME}
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${SFML_LINK_DLL} $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>)
        endforeach ()
    endif ()
endif ()

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif ()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

add_custom_command(TARGET ${EXECUTABLE_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
