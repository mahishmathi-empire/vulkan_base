#include "daagudumoothalu/daagudumoothalu.hpp"

int main()
{
  GLFWwindow* window;

  try
  {
    initWindow(1400, 1400, "Daagudumoothalu", window);
    testVulkan();
    testMath();
    mainLoop(window);
    cleanup(window);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
