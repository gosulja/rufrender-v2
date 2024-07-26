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

	glm::mat4 GetModelMatrix() const {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_position);
		model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, m_scale);
		return model;
	}

	void Draw(Shader* shader) {
		shader->use();
		m_texture->bind();
		shader->setMat4("model", GetModelMatrix());
		m_vao.bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		m_vao.unbind();
	}

private:
	VertexArray m_vao;
	Buffer m_vbo;
	Buffer m_ebo;
	std::unique_ptr<Texture> m_texture;
	unsigned int m_indexCount;

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
			{0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0},
			{1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))}
		};

		m_vao.addVertexBuffer(m_vbo, attributes);
		m_vao.bind();
		m_ebo.bind();
		m_vao.unbind();
	}
};

#endif
