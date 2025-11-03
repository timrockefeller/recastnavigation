file(GLOB TESTS_1_SOURCES *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Tests_1 ${TESTS_1_SOURCES})
add_dependencies(Tests_1 Recast Detour)
target_link_libraries(Tests_1 Recast Detour)
add_test(Tests_1 Tests_1)
