cmake_minimum_required(VERSION 2.6)
project(recordrgbddata)

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(recorder main.cpp)
target_link_libraries(recorder ${OpenCV_LIBS})



#install(TARGETS recordrgbddata RUNTIME DESTINATION bin)
