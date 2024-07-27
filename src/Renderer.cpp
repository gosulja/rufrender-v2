#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Callbacks.hpp"
#include "Texture.hpp"

void Renderer::Run() {
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	glEnable(GL_DEPTH_TEST);

	Texture texture("src/textures/wall.jpg", true);

	while (!glfwWindowShouldClose(m_Window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(m_Window, deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Gui->BeginFrame();

		texture.bind();

		glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

        m_LightingShader->use();
        m_LightingShader->setMat4("projection", projection);
        m_LightingShader->setMat4("view", view);

        m_LightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        m_LightingShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setVec3("lightPos", lightPos);
        m_LightingShader->setVec3("viewPos", camera->position);

        objectManager.DrawObjects(m_LightingShader, currentFrame);

        m_LightCubeShader->use();
        m_LightCubeShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        m_LightCubeShader->setMat4("model", m_lightCube->GetModelMatrix());
        m_LightCubeShader->setMat4("view", camera->GetViewMatrix());
        m_LightCubeShader->setMat4("projection", projection);

        m_lightCube->Draw(m_LightCubeShader, currentFrame);

        m_Gui->Draw(*camera);
        m_Gui->EndFrame();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	vao.unbind();

    m_Gui->~Gui();
}

void Renderer::setupScene() {
    std::vector<float> vertices = {
        // positions         // normal           // tex coords
        // front face
        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
        // back face
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        // left face
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        // right face
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         // top face
         -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
          0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
          0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
         // bottom face
         -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f
    };

    std::vector<unsigned int> indices = {
        0,  1,  2,  2,  3,  0,  // front face
        4,  5,  6,  6,  7,  4,  // back face
        8,  9, 10, 10, 11,  8,  // left face
        12, 13, 14, 14, 15, 12, // right face
        16, 17, 18, 18, 19, 16, // top face
        20, 21, 22, 22, 23, 20  // bottom face
    };

    std::vector<glm::vec3> positions = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f)
    };

    for (const auto& position : positions) {
        auto cube = std::make_unique<Object>(vertices, indices, "src/textures/wall.jpg");
        cube->SetPosition(position);
        objectManager.AddObject(std::move(cube));
    }

    m_lightCube = std::make_unique<Object>(vertices, indices, "src/textures/wall.jpg");
    m_lightCube->SetPosition(lightPos);
    m_lightCube->SetScale(glm::vec3(0.2f));

    vao.bind();
    vertexBuffer.setData(vertices);
    indexBuffer.setData(indices);

    std::vector<VertexAttribute> attributes = {
        {0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0},
        {1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))},
        {2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))}
    };

    vao.addVertexBuffer(vertexBuffer, attributes);

    // Setup light VAO
    light_vao.bind();
    lightbuffer.setData(vertices);
    light_vao.addVertexBuffer(lightbuffer, attributes);
}
