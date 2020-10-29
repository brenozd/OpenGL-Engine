#include "Shader.h"


Shader::Shader(std::string path)
{
    _shaderAttrib = parseShader(path);
    _shaderAttrib.id = compileShader(_shaderAttrib);
}

ShaderAttrib Shader::parseShader(std::string path)
{
    std::ifstream ifs(path);
    ShaderAttrib shaderP;

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
        buffer[length-1]='\0';
        shaderP.source = std::string(buffer);

        delete[] buffer;
    }

    //Get Shader Type
    std::map<std::string, ShaderType> sTypesMap;
    sTypesMap["vert"] = ShaderType::VERTEX;
    sTypesMap["frag"] = ShaderType::FRAGMENT;
    sTypesMap["comp"] = ShaderType::COMPUTE;

    std::string ext = path.substr(path.find_last_of(".") + 1);
    try
    {
        GLCall(shaderP.type = sTypesMap.at(ext));
    }
    catch (const std::exception &e)
    {
        shaderP.source = "";
        shaderP.type = ShaderType::NONE;
        std::cerr << e.what() << '\n';
    }
    return shaderP;
}

unsigned int Shader::compileShader(ShaderAttrib shaderProgram)
{
    std::map<ShaderType, unsigned int> glTypeMap;
    glTypeMap[ShaderType::VERTEX] = GL_VERTEX_SHADER;   //VERTEX
    glTypeMap[ShaderType::FRAGMENT] = GL_FRAGMENT_SHADER; //FRAGMENT
    glTypeMap[ShaderType::COMPUTE] = GL_COMPUTE_SHADER;  //COMPUTE

    unsigned int id = glCreateShader(glTypeMap.at(shaderProgram.type));
    const char *src = shaderProgram.source.c_str();
    int size = shaderProgram.source.length();
    glShaderSource(id, 1, &src, &size);
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

Shader::~Shader()
{
    glDeleteShader(_shaderAttrib.id);
}