#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Callbacks.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "ObjectManager.hpp"

class Renderer {
public:
    Renderer(GLFWwindow* window) 
        : m_Window(window), camera(new Camera(glm::vec3(5.0f, 0.0f, 3.0f))),
        vertexBuffer(Buffer::Type::VERTEX), 
        indexBuffer(Buffer::Type::INDEX),
        lastFrame(0.0f)
    {
        initShader();
        initCallbacks();
        setupScene();
    }

    ~Renderer() {
        if (m_Shader) {
            delete m_Shader;
        }
    }

    void Run();
private:
    GLFWwindow* m_Window;
    Shader* m_Shader;
    Camera* camera;
    ObjectManager objectManager;

    float lastFrame;

    VertexArray vao;
    Buffer vertexBuffer;
    Buffer indexBuffer;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void initShader() {
        const char* vertexPath = "src/shaders/default.vert";
        const char* fragmentPath = "src/shaders/default.frag";

        try {
            m_Shader = new Shader(vertexPath, fragmentPath);
        }
        catch (const std::exception& err) {
            std::cerr << "Failed to initialize shader: " << err.what() << "\n";
        }
    }

    void initCallbacks() {
        g_Camera = camera;

        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
        glfwSetCursorPosCallback(m_Window, mouse_callback);
        glfwSetScrollCallback(m_Window, scroll_callback);
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void setupScene();
};

#endif // RENDERER_HPP