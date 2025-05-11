cmake_minimum_required(VERSION 3.31)
project(vk)

set(CMAKE_CXX_STANDARD 23)

add_executable(vk main.cpp
        util.hpp
)
target_include_directories(vk PRIVATE
        "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\include"
        "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Include"
        "include"
)

target_link_directories(vk PRIVATE
        "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Lib"
        "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\lib-vc2022"
)

target_link_libraries(vk vulkan-1.lib glfw3.lib)