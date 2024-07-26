#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Camera.hpp"

class Renderer {
public:
    Renderer(GLFWwindow* window) 
        : m_Window(window), camera(nullptr),
        vertexBuffer(Buffer::Type::VERTEX), 
        indexBuffer(Buffer::Type::INDEX),
        lastFrame(0.0f)
    {
        initShader();
    }

    ~Renderer() {
        if (m_Shader) {
            delete m_Shader;
        }
    }

    void Run();
    void Scene(float dt);

private:
    GLFWwindow* m_Window;
    Shader* m_Shader;
    Camera* camera;

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

    void setupCube();
};

#endif // RENDERER_HPP