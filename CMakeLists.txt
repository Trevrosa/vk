cmake_minimum_required(VERSION 3.31)
project(vk)

set(CMAKE_CXX_STANDARD 23)

add_executable(vk main.cpp util.hpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # vulkan
    set(Vulkan_LIBRARIES
            "C:\\VulkanSDK\\1.4.313.0\\Lib"
            "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Lib"
    )
    set(Vulkan_INCLUDE_DIRS
            "C:\\VulkanSDK\\1.4.313.0\\Include"
            "C:\\Users\\trevo\\scoop\\apps\\vulkan\\current\\Lib\\Include"
    )
    # glfw
    set(GLFW_INCLUDE_DIRS
            "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\include"
    )
    set(GLFW_LIBRARIES
            "C:\\Users\\trevo\\scoop\\apps\\glfw\\current\\lib-vc2022"
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(GLFW_INCLUDE_DIRS "/usr/include")
    set(GLFW_LIBRARIES "/usr/lib")
endif()

target_include_directories(vk PRIVATE "include")

target_include_directories(vk PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_directories(vk PRIVATE ${Vulkan_LIBRARIES})

target_include_directories(vk PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_directories(vk PRIVATE ${GLFW_LIBRARIES})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(vk vulkan-1.lib glfw3.lib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(vk vulkan glfw3)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(vk vulkan glfw)
endif()
    