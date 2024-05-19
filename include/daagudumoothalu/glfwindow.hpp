#ifndef DAAGUDUMOOTHALU_GLFWINDOW_HPP
#define DAAGUDUMOOTHALU_GLFWINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

void initWindow(int width, int height, const char* title, GLFWwindow*& window);

void cleanup(GLFWwindow* window);

#endif // DAAGUDUMOOTHALU_GLFWINDOW_HPP