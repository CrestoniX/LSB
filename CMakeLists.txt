cmake_minimum_required(VERSION 3.5)


project(LSB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
add_executable(LSB main.cpp)
target_link_libraries (LSB pthread)
target_link_libraries(LSB ${OpenCV_LIBS})
