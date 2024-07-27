#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.hpp"
#include "Renderer.hpp"

#define WIDTH 1100
#define HEIGHT 700

int main() {
	Window* window = new Window(WIDTH, HEIGHT);
	Renderer renderer(window->GetWindow());

	renderer.Run();

	window->Terminate();

	return 0;
}