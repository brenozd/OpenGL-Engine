#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"

Texture2D::Texture2D(std::string path)
{
    _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    glGenTextures(1, &_rendererId);
    glBindTexture(GL_TEXTURE_2D, _rendererId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
    stbi_image_free(_data);
}

Texture2D::~Texture2D(){};

void Texture2D::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D, _rendererId);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture2D::byteArrayToInt(char* bytes, unsigned int count){
    int r;
    for(int i = 0; i < count; i++){
        r <<= 8;
        r |= (int)bytes[i] & 0xFF;
    }
    return (int)(r);
}