#include "shader_program.hpp"

//-----
ZameEngine::ShaderProgram::ShaderProgram(const char *vertexSourcePath, const char *fragmentSourcePath)
    : mInitialized(true), ID(0)
{
    //////////////////////////
    // Retrieve Source Code //
    //////////////////////////

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open the files
        vertexShaderFile.open(vertexSourcePath);
        fragmentShaderFile.open(fragmentSourcePath);

        std::stringstream vertexShaderStream, fragmentShaderStream;

        // Read in the file buffers
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // Close the files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert streams to strings
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        mInitialized = false;
        return;
    }

    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    /////////////////////
    // Compile Shaders //
    /////////////////////

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        mInitialized = false;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        mInitialized = false;
    }

    // Shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        mInitialized = false;
    }

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

//-----
void ZameEngine::ShaderProgram::use()
{
    if (mInitialized)
    {
        glUseProgram(ID);
    }
}

//-----
void ZameEngine::ShaderProgram::setBool(const std::string &name, bool value) const
{
    if (mInitialized)
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
    }
}

//-----
void ZameEngine::ShaderProgram::setInt(const std::string &name, int value) const
{
    if (mInitialized)
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
}

//-----
void ZameEngine::ShaderProgram::setFloat(const std::string &name, float value) const
{
    if (mInitialized)
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
}

//-----
void ZameEngine::ShaderProgram::setMat4(const std::string &name, const glm::mat4 &value) const
{
    if (mInitialized)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }
}
