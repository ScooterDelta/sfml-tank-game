set(SOURCE_FILES
        src/main.cpp)

set(LIBRARY_SOURCE_FILES
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
        src/Mine.cpp
        src/Mine.h
        src/Missile.cpp
        src/Missile.h
        src/NonAxisAligned.h
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

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCE_FILES})
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

    # Copy SFML Dll's to target output directory.
    # Only done on Windows if the SFML Root Dir variable is defined
    if (WIN32)
        foreach (SFML_PATH ${FIND_SFML_PATHS})
            if (IS_DIRECTORY ${SFML_PATH})
                file(GLOB SFML_LINK_DLLS "${SFML_PATH}/lib/*.dll")
                foreach (SFML_LINK_DLL ${SFML_LINK_DLLS})
                    add_custom_command(TARGET ${EXECUTABLE_NAME}
                            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                            ${SFML_LINK_DLL} $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>)
                endforeach ()
            endif ()
        endforeach ()
    endif ()
endif ()

add_custom_command(TARGET ${EXECUTABLE_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets)
