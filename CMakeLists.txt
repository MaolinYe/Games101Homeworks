cmake_minimum_required(VERSION 3.10)
project(Rasterizer)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR "C:\\opencv\\compile")
include_directories(${PROJECT_SOURCE_DIR}/eigen3)
add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(Rasterizer ${OpenCV_LIBS})