add_executable(recorder simple.cpp)
target_link_libraries(recorder ${OpenCV_LIBS})

add_executable(depth depth.cpp)
target_link_libraries(depth ${realsense2_LIBRARY})