cmake_minimum_required(VERSION 3.14)
project(NotcursesApp CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NOTCURSES REQUIRED notcurses)

set(SOURCES
    src/source.cpp
    src/InputHandler.cpp
    src/Renderer.cpp
)

add_executable(source ${SOURCES})

target_include_directories(source PRIVATE include ${NOTCURSES_INCLUDE_DIRS})
target_link_libraries(source ${NOTCURSES_LIBRARIES})
target_link_options(source PRIVATE ${NOTCURSES_LDFLAGS})