project (WORLD)
cmake_minimum_required (VERSION 2.8)
find_package (Qt5 COMPONENTS Widgets)
set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -ggdb -fPIE")

include_directories (${Qt5Widgets_INCLUDE_DIRS} ${WORLD_SOURCE_DIR}/src)
set (EXECUTABLE_OUTPUT_PATH "${WORLD_BINARY_DIR}/bin")

add_subdirectory (src)
