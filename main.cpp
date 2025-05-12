#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ranges>
#include <vector>
#include "util.hpp"

constexpr uint32_t WIDTH = 800, HEIGHT = 600;

const std::vector validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifndef _DEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

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
        window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle", nullptr, nullptr);
    }

    void initVulkan() {
        createVkInstance();
    }

    void createVkInstance() {
        std::cout << "creating vulkan instance" << std::endl;

        // ReSharper disable once CppRedundantBooleanExpressionArgument
        if (enableValidationLayers && !checkValidationLayerSupport(validationLayers)) {
            // ReSharper disable once CppRedundantBooleanExpressionArgument
            throw std::runtime_error("validation layers requested, but not available!");
        }

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

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            // ReSharper disable once CppDFAUnreachableCode
            createInfo.enabledLayerCount = 0;
        }

        auto extensions = getRequiredExtensions(enableValidationLayers);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef __APPLE__
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        std::cout << "enabled extensions (" << extensions.size() << "): ";
        for (const auto [idx, extension]: std::views::enumerate(extensions)) {
            std::cout << extension;
            if (idx != extensions.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";

        if (const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        std::cout << (requiredExtensionsAvailable(extensions) ? "all" : "not all") <<
                " required extensions are available" <<
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
