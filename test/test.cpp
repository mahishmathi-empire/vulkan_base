#include "daagudumoothalu/daagudumoothalu.hpp"

int main()
{
  GLFWwindow* window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

  try
  {
    initWindow(1400, 1400, "Daagudumoothalu", window);
    initVulkan(validationLayers, "Daagudumoothalu", instance, debugMessenger);
    testMath();
    mainLoop(window);
    cleanupVulkan(&instance, &debugMessenger);
    cleanup(window);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
