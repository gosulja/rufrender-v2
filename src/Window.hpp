#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Callbacks.hpp"

class Window {
public:
	Window(const int width, const int height) : width(width), height(height) {
		if (glfwInit() != GLFW_TRUE) {
			std::cerr << "Failed to initialize GLFW!\n";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, "rufrender", NULL, NULL);
		if (m_Window == NULL) {
			std::cerr << "Failed to create GLFW window!\n";
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetCursorPosCallback(m_Window, mouse_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);

		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		GLenum glewErr = glewInit();
		if (glewErr != GLEW_OK) {
			std::cerr << "Failed to initiate GLEW: " << glewGetErrorString(glewErr) << "\n";
		}

		glViewport(0, 0, width, height);
	}

	GLFWwindow *GetWindow();
	int GetWidth();
	int GetHeight();

	void Terminate();

private:
	int width, height;

	GLFWwindow* m_Window = nullptr;
};

#endif WINDOW_H
