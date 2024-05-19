#ifndef DAAGUDUMOOTHALU_VULKAN_HPP
#define DAAGUDUMOOTHALU_VULKAN_HPP

#include "daagudumoothalu/glfwindow.hpp"
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint>    // Necessary for uint32_t
#include <limits>     // Necessary for std::numeric_limits
#include <algorithm>  // Necessary for std::clamp
#include <fstream>

#ifdef ENABLE_VALIDATION_LAYERS
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

struct QueueFamilyIndices
{
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  bool isComplete()
  {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails
{
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

void initVulkan(const std::vector<const char*>& validationLayers, char const* title,
                VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger,
                VkPhysicalDevice physicalDevice, VkDevice& device, VkSurfaceKHR& surface,
                VkQueue& graphicsQueue, VkQueue& presentQueue,
                const std::vector<const char*>& deviceExtensions, GLFWwindow* window,
                VkSwapchainKHR& swapChain, std::vector<VkImage>& swapChainImages,
                VkFormat& swapChainImageFormat, VkExtent2D& swapChainExtent,
                std::vector<VkImageView>& swapChainImageViews,
                VkPipelineLayout& pipelineLayout, VkRenderPass& renderPass,
                VkPipeline& graphicsPipeline);

void createVkInstance(const std::vector<const char*>& validationLayers, char const* title,
                      VkInstance& instance);

void testVulkan();

// graphics pipeline methods
void createGraphicsPipeline(VkDevice device, VkPipelineLayout& pipelineLayout,
                            VkRenderPass& renderPass, VkPipeline& graphicsPipeline);

void createShaderModule(const std::vector<char>& code, VkDevice device,
                        VkShaderModule& shaderModule);

void createRenderPass(VkDevice device, VkFormat swapChainImageFormat,
                      VkRenderPass& renderPass);

// read binary file
void readBinaryFile(const std::string& filename, std::vector<char>& buffer);

// image views
void createImageViews(VkDevice device, const std::vector<VkImage>& swapChainImages,
                      VkFormat swapChainImageFormat,
                      std::vector<VkImageView>& swapChainImageViews);

// swap chain methods
bool checkDeviceExtensionSupport(VkPhysicalDevice device,
                                 const std::vector<const char*>& deviceExtensions);

void querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface,
                           SwapChainSupportDetails& swapChainSupport);

void chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats,
                             VkSurfaceFormatKHR& surfaceFormat);

void chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes,
                           VkPresentModeKHR& presentMode);

void chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window,
                      VkExtent2D& extent);

void createSwapChain(VkPhysicalDevice physicalDevice, VkDevice device,
                     VkSurfaceKHR& surface, GLFWwindow* window, VkSwapchainKHR& swapChain,
                     std::vector<VkImage>& swapChainImages,
                     VkFormat& swapChainImageFormat, VkExtent2D& swapChainExtent);

// surface
void createSurface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR& surface);

// logical device methods
void createLogicalDevice(VkPhysicalDevice physicalDevice,
                         const std::vector<const char*>& validationLayers,
                         VkDevice& device, VkSurfaceKHR& surface, VkQueue& graphicsQueue,
                         VkQueue& presentQueue,
                         const std::vector<const char*>& deviceExtensions);

// physical device methods
bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface,
                      const std::vector<const char*>& deviceExtensions);

void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice& physicalDevice,
                        VkSurfaceKHR& surface,
                        const std::vector<const char*>& deviceExtensions);

void findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface,
                       QueueFamilyIndices& indices);

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

void cleanupVulkan(VkSurfaceKHR* surface, VkInstance* instance,
                   VkDebugUtilsMessengerEXT* debugMessenger, VkDevice* device,
                   VkSwapchainKHR* swapChain,
                   std::vector<VkImageView>& swapChainImageViews,
                   VkPipelineLayout* pipelineLayout, VkRenderPass* renderPass,
                   VkPipeline* graphicsPipeline);

#endif  // DAAGUDUMOOTHALU_VULKAN_HPP