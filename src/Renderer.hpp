#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include "Gui.hpp"
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
        : m_Window(window), camera(new Camera(glm::vec3(5.0f, 0.0f, 3.0f))), m_Gui(nullptr),
        vertexBuffer(Buffer::Type::VERTEX), 
        indexBuffer(Buffer::Type::INDEX),
        lastFrame(0.0f), lightbuffer(Buffer::Type::VERTEX), lightPos(1.2f, 1.0f, 2.0f)
    {
        initShader();
        initCallbacks();
        setupScene();

        m_Gui = new Gui(window, &objectManager);
    }

    ~Renderer() {
        if (m_DefaultShader) {
            delete m_DefaultShader;
        }

        if (m_LightingShader) {
            delete m_LightingShader;
        }
    }

    void Run();
private:
    GLFWwindow* m_Window;
    Shader* m_DefaultShader;
    Shader* m_LightingShader;
    Shader* m_LightCubeShader;
    Gui* m_Gui;
    Camera* camera;
    ObjectManager objectManager;

    float lastFrame;

    VertexArray vao;
    Buffer vertexBuffer;
    Buffer indexBuffer;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    VertexArray light_vao;
    Buffer lightbuffer;

    std::unique_ptr<VertexArray> m_lightVAO;
    std::unique_ptr<Buffer> m_lightVBO;

    glm::vec3 lightPos;

    std::unique_ptr<Object> m_lightCube;

    void initShader() {
        try {
            m_DefaultShader = new Shader("src/shaders/default.vert", "src/shaders/default.frag");
            m_LightingShader = new Shader("src/shaders/lighting.vert", "src/shaders/lighting.frag");
            m_LightCubeShader = new Shader("src/shaders/light_cube.vert", "src/shaders/light_cube.frag");
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