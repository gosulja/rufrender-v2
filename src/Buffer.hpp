#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <GL/glew.h>
#include <vector>

class Buffer {
public:
	enum class Type {
		VERTEX,
		INDEX,
		UNIFORM
	};

	Buffer(Type type) : m_type(type), m_bufferId(0) {}

	~Buffer() {
		if (m_bufferId != 0) {
			glDeleteBuffers(1, &m_bufferId);
		}
	}

	void bind() const {
		glBindBuffer(getBufferType(), m_bufferId);
	}
	
	void unbind() const {
		glBindBuffer(getBufferType(), 0);
	}

	template<typename T>
	void setData(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
		if (m_bufferId == 0) {
			glGenBuffers(1, &m_bufferId);
		}

		bind();
		glBufferData(getBufferType(), data.size() * sizeof(T), data.data(), usage);
		unbind();
	}

	GLuint getId() const { return m_bufferId; }

private:
	Type m_type;
	GLuint m_bufferId;

	GLenum getBufferType() const {
		switch (m_type) {
			case Type::VERTEX: return GL_ARRAY_BUFFER;
			case Type::INDEX: return GL_ELEMENT_ARRAY_BUFFER;
			case Type::UNIFORM: return GL_UNIFORM_BUFFER;
			default: return GL_ARRAY_BUFFER;
		}
	}
};

#endif BUFFER_HPP