project(columns)

SET(execName columns)

set (CMAKE_CXX_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(${execName} main.cpp ../../ezViz.hpp)

TARGET_LINK_LIBRARIES(${execName} ${CURSES_LIBRARIES})
