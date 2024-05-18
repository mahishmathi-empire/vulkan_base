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

  const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

  try
  {
    initWindow(1400, 1400, "Daagudumoothalu", window);
    initVulkan(validationLayers, "Daagudumoothalu", instance, debugMessenger,
               physicalDevice, device, surface, graphicsQueue, presentQueue);
    createSurface(instance, window, surface);
    testMath();
    mainLoop(window);
    cleanupVulkan(&surface, &instance, &debugMessenger, &device);
    cleanup(window);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
