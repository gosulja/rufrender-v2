#include "stb_image.h"
#include "Texture.hpp"
#include <iostream>

Texture::Texture(const std::string& path, bool generateMipmap)
    : m_rendererId(0), m_filePath(path), m_localBuffer(nullptr),
    m_width(0), m_height(0), m_bpp(0), m_generateMipmap(generateMipmap)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    if (m_localBuffer) {
        glGenTextures(1, &m_rendererId);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_generateMipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);

        if (m_generateMipmap) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(m_localBuffer);
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_rendererId);
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}