#ifndef UTIL_H
#define UTIL_H
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

inline std::vector<const char *> getRequiredExtensions(const bool enableValidationLayers) {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#if __APPLE__
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

inline bool checkValidationLayerSupport(const std::vector<const char *>& validationLayers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName: validationLayers) {
        bool layerFound = false;

        for (const auto &layerProperties: availableLayers) {
            if (std::strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

static bool requiredExtensionsAvailable(const std::vector<const char *>& requiredExtensions) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    for (uint32_t i = 0; i < requiredExtensions.size(); i++) {
        if (i > 0)
            std::cout << "\n";

        const char *extension = requiredExtensions[i];
        std::cout << "need " << extension << ".. ";

        bool found = false;

        for (const auto &[availableExtensionName, specVersion]: availableExtensions) {
            if (std::strcmp(extension, availableExtensionName) == 0) {
                std::cout << "found with spec version " << specVersion;
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
            std::cout << "not found";
        }
    }

    std::cout << "\n";
    return true;
}
