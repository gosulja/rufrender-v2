#pragma once

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Object {
public:
	Object(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const char* texturePath)
		: m_position(0.0f), m_rotation(0.0f), m_scale(1.0f), m_vbo(Buffer::Type::VERTEX), m_ebo(Buffer::Type::INDEX) {
		setupMesh(vertices, indices);
		m_texture = std::make_unique<Texture>(texturePath, true);
	}

	void SetPosition(const glm::vec3& position) { m_position = position; }
	void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
	void SetScale(const glm::vec3& scale) { m_scale = scale; }

	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetRotation() { return m_rotation; }
	glm::vec3 GetScale() { return m_scale; }

	glm::mat4 GetModelMatrix() const {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_position);
		model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, m_scale);
		return model;
	}

	void SetShader(Shader* shader) { m_shader = shader; }
	Shader* GetShader() const { return m_shader; }

	void Draw(Shader* shader, float dt) {
		shader->use();
		m_texture->bind();
		shader->setMat4("model", GetModelMatrix());
		m_vao.bind();

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		m_vao.unbind();
	}

	std::string GetInfo() const {
		std::string info = "Object Info:\n";
		info += "Position: (" + std::to_string(m_position.x) + ", " + std::to_string(m_position.y) + ", " + std::to_string(m_position.z) + ")\n";
		info += "Rotation: (" + std::to_string(m_rotation.x) + ", " + std::to_string(m_rotation.y) + ", " + std::to_string(m_rotation.z) + ")\n";
		info += "Scale: (" + std::to_string(m_scale.x) + ", " + std::to_string(m_scale.y) + ", " + std::to_string(m_scale.z) + ")\n";
		return info;
	}
private:
	VertexArray m_vao;
	Buffer m_vbo;
	Buffer m_ebo;
	std::unique_ptr<Texture> m_texture;
	unsigned int m_indexCount;

	Shader* m_shader;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	void setupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
		m_vbo = Buffer(Buffer::Type::VERTEX);
		m_vbo.setData(vertices);

		m_ebo = Buffer(Buffer::Type::INDEX);
		m_ebo.setData(indices);

		m_indexCount = indices.size();

		std::vector<VertexAttribute> attributes = {
			{0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0},
			{1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))},
			{2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))}
		};

		m_vao.addVertexBuffer(m_vbo, attributes);
		m_vao.bind();
		m_ebo.bind();
		m_vao.unbind();
	}
};

#endif
