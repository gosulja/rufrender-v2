#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Callbacks.hpp"
#include "Texture.hpp"

void Renderer::Run() {
	glEnable(GL_DEPTH_TEST);

	Texture texture("src/textures/wall.jpg", true);

	while (!glfwWindowShouldClose(m_Window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(m_Window, deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.bind();

		m_Shader->use();

		glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

		m_Shader->setMat4("projection", projection);
		m_Shader->setMat4("view", view);

		m_Shader->setInt("aTexture", 0);

        objectManager.DrawObjects(m_Shader);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	vao.unbind();
}

void Renderer::setupScene() {
    std::vector<float> vertices = {
        // positions          // tex coords
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        // back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        // left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        // right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         // top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         // bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f
    };

    std::vector<unsigned int> indices = {
        0,  1,  2,  2,  3,  0,  // front face
        4,  5,  6,  6,  7,  4,  // back face
        8,  9, 10, 10, 11,  8,  // left face
        12, 13, 14, 14, 15, 12,  // right face
        16, 17, 18, 18, 19, 16,  // top face
        20, 21, 22, 22, 23, 20   // bottom face
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
}

/*
void Renderer::Scene(float dt) {
    std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f)
    };

    vao.bind();
    indexBuffer.bind();

    for (unsigned int i = 0; i < cubePositions.size(); i++) {
        float oscillation = cos(dt * 3.0f + i * 0.5f);
        float rotationAngle = oscillation * glm::radians(45.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);

        glm::vec3 rotationAxis = glm::normalize(glm::vec3(1.0f + i * 0.2f, 0.3f + i * 0.1f, 0.5f + i * 0.15f));
        model = glm::rotate(model, rotationAngle, rotationAxis);

        float additionalRotation = sin(dt * (20.0f + i * 5.0f));
        model = glm::rotate(model, glm::radians(additionalRotation), glm::vec3(0.0f, 1.0f, 0.0f));

        m_Shader->setMat4("model", model);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }

    vao.unbind();
}
*/