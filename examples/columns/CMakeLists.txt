project(columns)

SET(execName columns)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(${execName} main.cpp)

TARGET_LINK_LIBRARIES(${execName} ${CURSES_LIBRARIES})
