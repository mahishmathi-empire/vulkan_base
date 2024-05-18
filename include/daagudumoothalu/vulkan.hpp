#ifndef DAAGUDUMOOTHALU_VULKAN_HPP
#define DAAGUDUMOOTHALU_VULKAN_HPP

#include "daagudumoothalu/glfwindow.hpp"
#include <vector>
#include <cstring>
#include <optional>

#ifdef ENABLE_VALIDATION_LAYERS
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

struct QueueFamilyIndices
{
  std::optional<uint32_t> graphicsFamily;

  bool isComplete()
  {
    return graphicsFamily.has_value();
  }
};

void initVulkan(const std::vector<const char*>& validationLayers, char const* title,
                VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger,
                VkDevice& device);

void createVkInstance(const std::vector<const char*>& validationLayers, char const* title,
                      VkInstance& instance);

void testVulkan();

// logical device methods
void createLogicalDevice(VkPhysicalDevice physicalDevice,
                         const std::vector<const char*>& validationLayers,
                         VkDevice& device);

// physical device methods
bool isDeviceSuitable(VkPhysicalDevice device);

void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice& physicalDevice);

void findQueueFamilies(VkPhysicalDevice device, QueueFamilyIndices& indices);

// validation layer methods

bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers);

void getRequiredExtensions(std::vector<const char*>& extensions);

// debug methods

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

// cleanup methods

void cleanupVulkan(VkInstance* instance, VkDebugUtilsMessengerEXT* debugMessenger,
                   VkDevice* device);

#endif  // DAAGUDUMOOTHALU_VULKAN_HPP