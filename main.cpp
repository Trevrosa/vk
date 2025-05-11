#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ranges>
#include <vector>
#include "util.hpp"

constexpr uint32_t WIDTH = 800, HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window = nullptr;
    VkInstance instance = nullptr;

    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        createVkInstance();
    }

    void createVkInstance() {
        std::cout << "creating vulkan instance" << std::endl;

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 6, 9);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
        appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

#if __APPLE__
    std::vector<const char*> requiredExtensions;

    for(uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }

    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
#else
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
#endif
        createInfo.enabledLayerCount = 0;

        const std::vector<std::string> glfwExtensionsVector(glfwExtensions, glfwExtensions + glfwExtensionCount);
        std::cout << "enabled extensions (" << glfwExtensionCount << "): ";
        for (const auto [idx, extension] : std::views::enumerate(glfwExtensionsVector)) {
            std::cout << extension;
            if (idx != glfwExtensionCount - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";

        if (const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        std::cout << (allRequiredExtensionsAvailable() ? "all" : "not all") << " required extensions are available" <<
                std::endl;

        std::cout << "created vulkan instance" << std::endl;
    }

    void mainLoop() const {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() const {
        std::cout << "\ncleaning up" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    try {
        HelloTriangleApplication app;
        app.run();
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
