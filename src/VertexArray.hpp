#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "Buffer.hpp"

struct VertexAttribute {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* pointer;
};

class VertexArray {
public:
	VertexArray() {
		glGenVertexArrays(1, &m_vaoId);
	}

    ~VertexArray() {
        glDeleteVertexArrays(1, &m_vaoId);
    }

    void bind() const {
        glBindVertexArray(m_vaoId);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void addVertexBuffer(const Buffer& vbo, const std::vector<VertexAttribute>& attributes) {
        bind();
        vbo.bind();

        for (const auto& attr : attributes) {
            glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.pointer);
            glEnableVertexAttribArray(attr.index);
        }

        unbind();
    }
private:
	GLuint m_vaoId;
};

#endif VERTEXARRAY_HPP