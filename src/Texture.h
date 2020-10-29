#ifndef Texture_h
#define Texture_h

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

class Texture2D{
private:
    unsigned int _rendererId = 0;
    int _width = 0;
    int _height = 0;
    int _channels = 0;
    unsigned char* _data;

    int byteArrayToInt(char* bytes, unsigned int count);

public:
    Texture2D(std::string path);
    ~Texture2D();

    inline unsigned int getWidth() const {return _width;}
    inline unsigned int getHeigth() const {return _height;};
    inline unsigned int getChannels() const {return _channels;};
    inline unsigned char* getData() const {return _data;};

    void bind(unsigned int slot);
    void unbind();
};
#endif