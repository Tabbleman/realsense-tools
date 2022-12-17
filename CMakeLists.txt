cmake_minimum_required(VERSION 2.6)
project(recordrgbddata)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(realsense2 REQUIRED)

add_subdirectory(tools)





#install(TARGETS recordrgbddata RUNTIME DESTINATION bin)
