#ifndef DAAGUDUMOOTHALU_VULKAN_HPP
#define DAAGUDUMOOTHALU_VULKAN_HPP

#include "daagudumoothalu/glfwindow.hpp"
#include <vector>
#include <cstring>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void initVulkan(const std::vector<const char*>& validationLayers, char const* title,
                VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);

void createVkInstance(const std::vector<const char*>& validationLayers, char const* title,
                      VkInstance& instance);

void testVulkan();

bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers);

void getRequiredExtensions(std::vector<const char*>& extensions);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

void setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT& debugMessenger);

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks* pAllocator);

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

void cleanupVulkan(VkInstance* instance, VkDebugUtilsMessengerEXT* debugMessenger);

#endif  // DAAGUDUMOOTHALU_VULKAN_HPP