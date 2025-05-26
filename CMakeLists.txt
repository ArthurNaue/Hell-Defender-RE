cmake_minimum_required(VERSION 3.10)
project(main C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES "src/*.c")

include_directories(include)

add_executable(main ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(main raylib m)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:main>/assets
)