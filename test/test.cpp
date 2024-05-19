#include "daagudumoothalu/daagudumoothalu.hpp"

int main()
{
  GLFWwindow* window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkSurfaceKHR surface;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
  VkSwapchainKHR swapChain;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  VkPipelineLayout pipelineLayout;
  VkRenderPass renderPass;
  VkPipeline graphicsPipeline;
  VkCommandPool commandPool;
  VkCommandBuffer commandBuffer;
  VkSemaphore imageAvailableSemaphore;
  VkSemaphore renderFinishedSemaphore;
  VkFence inFlightFence;

  const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
  const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;

  try
  {
    initWindow(1400, 1400, "Daagudumoothalu", window);
    initVulkan(validationLayers, "Daagudumoothalu", instance, debugMessenger,
               physicalDevice, device, surface, graphicsQueue, presentQueue,
               deviceExtensions, window, swapChain, swapChainImages, swapChainImageFormat,
               swapChainExtent, swapChainImageViews, pipelineLayout, renderPass,
               graphicsPipeline, swapChainFramebuffers, commandPool, commandBuffer,
               imageAvailableSemaphore, renderFinishedSemaphore, inFlightFence);
    // testMath();
    mainLoop(window, device, graphicsQueue, presentQueue, swapChain, swapChainImages,
             imageAvailableSemaphore, renderFinishedSemaphore, inFlightFence,
             commandBuffer, graphicsPipeline, renderPass, swapChainExtent,
             swapChainFramebuffers);
    cleanupVulkan(&surface, &instance, &debugMessenger, &device, &swapChain,
                  swapChainImageViews, &pipelineLayout, &renderPass, &graphicsPipeline,
                  swapChainFramebuffers, &commandPool, &commandBuffer,
                  &imageAvailableSemaphore, &renderFinishedSemaphore, &inFlightFence);
    cleanup(window);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
