#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Callbacks.hpp"
#include "Texture.hpp"

void Renderer::setupCube() {
    vertices = {
        // Positions          // Texture Coords
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         // Bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f
    };

    indices = {
         0,  1,  2,  2,  3,  0,  // Front face
         4,  5,  6,  6,  7,  4,  // Back face
         8,  9, 10, 10, 11,  8,  // Left face
        12, 13, 14, 14, 15, 12,  // Right face
        16, 17, 18, 18, 19, 16,  // Top face
        20, 21, 22, 22, 23, 20   // Bottom face
    };

    vertexBuffer = Buffer(Buffer::Type::VERTEX);
    vertexBuffer.setData(vertices);

    indexBuffer = Buffer(Buffer::Type::INDEX);
    indexBuffer.setData(indices);

    std::vector<VertexAttribute> attributes = {
        {0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0},
        {1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))}
    };

    vao.addVertexBuffer(vertexBuffer, attributes);
}

void Renderer::Run() {
    setupCube();

	glEnable(GL_DEPTH_TEST);

	Texture texture("src/textures/wall.jpg", true);

	while (!glfwWindowShouldClose(m_Window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		processInput(m_Window, camera, deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.bind();

		m_Shader->use();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		m_Shader->setMat4("view", view);
		m_Shader->setMat4("projection", projection);

		m_Shader->setInt("aTexture", 0);

		Scene(deltaTime);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	vao.unbind();
}

// Draw here
void Renderer::Scene(float dt) {
    float oscillation = std::sin(dt * 0.5f);
    float rotationAngle = oscillation * glm::radians(45.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotationAngle, glm::vec3(0.5f, 9.0f, rotationAngle * 2.0f));
    m_Shader->setMat4("model", model);

    vao.bind();
    indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}
