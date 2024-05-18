#ifndef DAAGUDUMOOTHALU_VULKAN_HPP
#define DAAGUDUMOOTHALU_VULKAN_HPP

#include "daagudumoothalu/glfwindow.hpp"

void initVulkan();

void createVkInstance(char const* title, VkInstance& instance);

void testVulkan();

void cleanupVulkan(VkInstance *instance);

#endif // DAAGUDUMOOTHALU_VULKAN_HPP