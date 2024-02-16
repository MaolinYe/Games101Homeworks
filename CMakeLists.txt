cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing Assignment6/PA6/Assignment6/main.cpp Assignment6/PA6/Assignment6/Object.hpp Assignment6/PA6/Assignment6/Vector.cpp Assignment6/PA6/Assignment6/Vector.hpp Assignment6/PA6/Assignment6/Sphere.hpp Assignment6/PA6/Assignment6/global.hpp Assignment6/PA6/Assignment6/Triangle.hpp Assignment6/PA6/Assignment6/Scene.cpp
        Assignment6/PA6/Assignment6/Scene.hpp Assignment6/PA6/Assignment6/Light.hpp Assignment6/PA6/Assignment6/AreaLight.hpp Assignment6/PA6/Assignment6/BVH.cpp Assignment6/PA6/Assignment6/BVH.hpp Assignment6/PA6/Assignment6/Bounds3.hpp Assignment6/PA6/Assignment6/Ray.hpp Assignment6/PA6/Assignment6/Material.hpp Assignment6/PA6/Assignment6/Intersection.hpp
        Assignment6/PA6/Assignment6/Renderer.cpp Assignment6/PA6/Assignment6/Renderer.hpp)
