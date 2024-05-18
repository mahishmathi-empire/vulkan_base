#include "daagudumoothalu/glfwindow.hpp"

void initWindow(int width, int height, const char* title, GLFWwindow*& window)
{
  if (!glfwInit())
  {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

void mainLoop(GLFWwindow* window)
{
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }
}

void cleanup(GLFWwindow* window)
{
  glfwDestroyWindow(window);
  glfwTerminate();
}