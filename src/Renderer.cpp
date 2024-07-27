#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Callbacks.hpp"
#include "Texture.hpp"

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

void Renderer::Run() {
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(m_Window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(m_Window, deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Gui->BeginFrame();

		glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();

        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        m_LightingShader->use();
        m_LightingShader->setMat4("projection", projection);
        m_LightingShader->setMat4("view", view);

        m_LightingShader->setInt("material.diffuse", 0);
        m_LightingShader->setInt("material.specular", 1);
        m_LightingShader->setFloat("material.shininess", 64.0f);

        m_LightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_LightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_LightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_LightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        m_LightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
        m_LightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        m_LightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        m_LightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setFloat("pointLights[0].constant", 1.0f);
        m_LightingShader->setFloat("pointLights[0].linear", 0.09f);
        m_LightingShader->setFloat("pointLights[0].quadratic", 0.032f);

        m_LightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
        m_LightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        m_LightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        m_LightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setFloat("pointLights[1].constant", 1.0f);
        m_LightingShader->setFloat("pointLights[1].linear", 0.09f);
        m_LightingShader->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        m_LightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
        m_LightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        m_LightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        m_LightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setFloat("pointLights[2].constant", 1.0f);
        m_LightingShader->setFloat("pointLights[2].linear", 0.09f);
        m_LightingShader->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        m_LightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
        m_LightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        m_LightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        m_LightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setFloat("pointLights[3].constant", 1.0f);
        m_LightingShader->setFloat("pointLights[3].linear", 0.09f);
        m_LightingShader->setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        m_LightingShader->setVec3("spotLight.position", camera->position);
        m_LightingShader->setVec3("spotLight.direction", camera->front);
        m_LightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        m_LightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        m_LightingShader->setFloat("spotLight.constant", 1.0f);
        m_LightingShader->setFloat("spotLight.linear", 0.09f);
        m_LightingShader->setFloat("spotLight.quadratic", 0.032f);
        m_LightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        m_LightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        m_LightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        m_LightingShader->setVec3("lightColor", lightColor);
        m_LightingShader->setVec3("light.position", lightPos);
        m_LightingShader->setVec3("light.direction", camera->front);
        m_LightingShader->setVec3("viewPos", camera->position);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

        m_LightingShader->setVec3("light.ambient", ambientColor);
        m_LightingShader->setVec3("light.diffuse", diffuseColor);
        m_LightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        m_LightingShader->setFloat("light.constant", 1.0f);
        m_LightingShader->setFloat("light.linear", 0.09f);
        m_LightingShader->setFloat("light.quadratic", 0.032f);

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
        auto cube = std::make_unique<Object>(vertices, indices, "src/textures/container2.png", "src/textures/container2_specular.png");
        cube->SetPosition(position);
        objectManager.AddObject(std::move(cube));
    }

    m_lightCube = std::make_unique<Object>(vertices, indices, "src/textures/container2.png", "src/textures/container2_specular.png");
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

    light_vao.bind();
    lightbuffer.setData(vertices);
    light_vao.addVertexBuffer(lightbuffer, attributes);
}
