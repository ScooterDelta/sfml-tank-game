set(TEST_SOURCE_FILES
        src/TankGameTests.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/main/src
        ${Boost_INCLUDE_DIRS})

add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(${TEST_EXECUTABLE_NAME}
        ${LIBRARY_NAME}
        ${Boost_LIBRARIES})

add_test(NAME GAME_TESTS COMMAND ${TEST_EXECUTABLE_NAME})
