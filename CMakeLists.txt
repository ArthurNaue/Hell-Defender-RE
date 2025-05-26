cmake_minimum_required(VERSION 3.10)
project(HellDefenderRE C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
include_directories(libraries/raylib/src)

add_subdirectory(libraries/raylib)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(HellDefender ${SOURCES})

if(WIN32)
    target_link_libraries(HellDefender raylib winmm gdi32)
elseif(APPLE)
    target_link_libraries(HellDefender raylib m)
else()
    target_link_libraries(HellDefender raylib m pthread dl rt GL)
endif()

add_custom_command(TARGET HellDefender POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:HellDefender>/assets
)
