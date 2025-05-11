#ifndef UTIL_H
#define UTIL_H
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

static bool allRequiredExtensionsAvailable() {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    uint32_t requiredExtensionCount = 0;
    const char **requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionCount);

    bool found = false;

    for (uint32_t i = 0; i < requiredExtensionCount; i++) {
        if (i > 0)
            std::cout << "\n";

        const char *extension = requiredExtensions[i];
        std::cout << "need " << extension << ".. ";

        bool thisFound = false;

        for (const auto &[availableExtensionName, specVersion]: availableExtensions) {
            if (std::strcmp(extension, availableExtensionName) != 0) {
                std::cout << "found with spec version " << specVersion;
                thisFound = true;
                break;
            }
        }

        if (thisFound) {
            found = true;
        } else {
            found = false;
            std::cout << "not found";
        }
    }

    std::cout << "\n";
    return found;
}
