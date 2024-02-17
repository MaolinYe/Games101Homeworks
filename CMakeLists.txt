cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing Assignment7/main.cpp Assignment7/Object.hpp Assignment7/Vector.cpp Assignment7/Vector.hpp Assignment7/Sphere.hpp Assignment7/global.hpp Assignment7/Triangle.hpp Assignment7/Scene.cpp
        Assignment7/Scene.hpp Assignment7/Light.hpp Assignment7/AreaLight.hpp Assignment7/BVH.cpp Assignment7/BVH.hpp Assignment7/Bounds3.hpp Assignment7/Ray.hpp Assignment7/Material.hpp Assignment7/Intersection.hpp
        Assignment7/Renderer.cpp Assignment7/Renderer.hpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp")
