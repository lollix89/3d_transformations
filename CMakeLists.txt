cmake_minimum_required(VERSION 3.15)
project(3d_transform)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(3d_transform main.cpp Transformations.cpp)
target_link_libraries(3d_transform ${OpenCV_LIBS})