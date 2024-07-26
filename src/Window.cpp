#pragma once
#include "Window.hpp"

GLFWwindow *Window::GetWindow() {
	return m_Window;
}

int Window::GetWidth() { return width; }
int Window::GetHeight() { return height; }

void Window::Terminate() {
	glfwTerminate();
}
