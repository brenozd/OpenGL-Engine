#include "Shader.h"

ShaderProgram Shader::parseShader(std::string path)
{
    std::ifstream ifs(path);
    ShaderProgram shaderP;

    //Read shader code
    if (ifs.is_open())
    {
        ifs.seekg(0, ifs.end);
        int length = ifs.tellg();
        ifs.seekg(0, ifs.beg);

        char *buffer = new char[length];

        ifs.read(buffer, length);

        if (!ifs)
            std::cout << "ERROR -  read only " << ifs.gcount() << "characters" << std::endl;

        ifs.close();

        shaderP.source = std::string(buffer);

        delete[] buffer;
    }

    //Get Shader Type
    std::map<std::string, ShaderType> sTypesMap;
    sTypesMap["vertex"] = ShaderType::VERTEX;
    sTypesMap["fragment"] = ShaderType::FRAGMENT;
    sTypesMap["compute"] = ShaderType::COMPUTE;

    std::string ext = path.substr(path.find_last_of(".") + 1);
    try
    {
        shaderP.type = sTypesMap.at(ext);
    }
    catch (const std::exception &e)
    {
        shaderP.source = "";
        shaderP.type = ShaderType::NONE;
        std::cerr << e.what() << '\n';
    }

    return shaderP;
}

unsigned int Shader::compileShader(ShaderProgram shaderProgram)
{
    std::map<ShaderType, unsigned int> glTypeMap;
    glTypeMap[ShaderType::VERTEX] = 0x8B31;   //VERTEX
    glTypeMap[ShaderType::FRAGMENT] = 0x8B30; //FRAGMENT
    glTypeMap[ShaderType::COMPUTE] = 0X91B9;  //COMPUTE

    unsigned int id = glCreateShader(glTypeMap.at(shaderProgram.type));
    const char *src = shaderProgram.source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader..." << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

Shader::Shader(std::string path)
{
    _shaderProgram = parseShader(path);
    _shaderProgram.id = compileShader(_shaderProgram);
    unsigned int program = glCreateProgram();
    glAttachShader(program, _shaderProgram.id);
    glLinkProgram(program);
    glValidateProgram(program);
    glDetachShader(program, _shaderProgram.id);
    glDeleteShader(_shaderProgram.id);

    _rendererId = program;
}

Shader::~Shader()
{
    glDeleteProgram(_rendererId);
}

void Shader::bind()
{
    glUseProgram(_rendererId);
}

unsigned int Shader::bind(std::string path)
{
    ShaderProgram shaderProgram = parseShader(path);
    unsigned int program = glCreateProgram();
    unsigned int shader = compileShader(shaderProgram);
    glAttachShader(program, shader);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(shader);
    glUseProgram(program);

    return program;
}

void Shader::unbind()
{
    GLCall(glUseProgram(0));
}

int Shader::setUniform4f(std::string param, float v1, float v2, float v3, float v4)
{
    bind();
    if (_rendererId == 0)
        return 0;
    GLCall(glUniform4f(getUniformLocation(param), v1, v2, v3, v4));
    return 1;
}

int Shader::getUniformLocation(std::string uniform)
{
    if(_uniformsCache.find(uniform) != _uniformsCache.end())
        return _uniformsCache[uniform];
    else{
        int location = glGetUniformLocation(_rendererId, uniform.c_str());
        _uniformsCache[uniform] = location;
        return location;
    }
}