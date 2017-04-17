set(SOURCE_FILES
        src/main.cpp)

set(LIBRARY_SOURCE_FILES
        src/game/utility/Angle.cpp
        src/game/utility/Angle.h
        src/game/domain/AxisAligned.h
        src/game/gameplay/Battle.cpp
        src/game/gameplay/Battle.h
        src/game/display/Display.cpp
        src/game/display/Display.h
        src/game/domain/DrawableObject.h
        src/game/domain/Explosion.cpp
        src/game/domain/Explosion.h
        src/game/gameplay/Gameplay.h
        src/game/display/HUD.cpp
        src/game/display/HUD.h
        src/game/domain/Mine.cpp
        src/game/domain/Mine.h
        src/game/domain/Missile.cpp
        src/game/domain/Missile.h
        src/game/domain/NonAxisAligned.h
        src/game/domain/Obstacle.cpp
        src/game/domain/Obstacle.h
        src/game/gameplay/Score.cpp
        src/game/gameplay/Score.h
        src/game/domain/Tank.cpp
        src/game/domain/Tank.h
        src/game/domain/Turret.cpp
        src/game/domain/Turret.h
        src/game/utility/Vector2D.cpp
        src/game/utility/Vector2D.h)

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
