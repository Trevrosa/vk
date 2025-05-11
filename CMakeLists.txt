cmake_minimum_required(VERSION 3.31)
project(vk)

set(CMAKE_CXX_STANDARD 23)

add_executable(vk main.cpp util.hpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(vk PRIVATE
            "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\include"
            "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Include"
            "include"
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_include_directories(vk PRIVATE
            "/usr/include"
            "/usr/local/include"
            "include"
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_include_directories(vk PRIVATE
            "/usr/local/include"
            "include"
    )
endif ()


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_directories(vk PRIVATE
            "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Lib"
            "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\lib-vc2022"
    )
    target_link_libraries(vk vulkan-1.lib glfw3.lib)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(vk vulkan glfw3)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(vk vulkan glfw)
endif ()
