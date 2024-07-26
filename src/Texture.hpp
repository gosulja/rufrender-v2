#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(const std::string& path, bool generateMipmap = true);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }

private:
    unsigned int m_rendererId;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_bpp;
    bool m_generateMipmap;
};

#endif // TEXTURE_HPP