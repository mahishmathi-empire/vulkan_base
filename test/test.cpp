#include "daagudumoothalu/daagudumoothalu.hpp"

int main()
{
  GLFWwindow* window;
  VkInstance instance;

  try
  {
    initWindow(1400, 1400, "Daagudumoothalu", window);
    createVkInstance("Daagudumoothalu", instance);
    testMath();
    mainLoop(window);
    cleanupVulkan(&instance);
    cleanup(window);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
