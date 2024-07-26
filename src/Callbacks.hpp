#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

extern Camera* g_Camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);