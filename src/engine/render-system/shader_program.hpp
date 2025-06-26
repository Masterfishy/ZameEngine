#pragma once

// Emscripten includes
#include <GLES3/gl3.h>

// GLM includes
#include <glm/glm.hpp>

// System includes
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ZameEngine
{
class ShaderProgram
{
  private:
    /// @brief The initialized state of the shader program.
    bool mInitialized;

  public:
    /// @brief The shader program ID.
    unsigned int ID;

    /// @brief Read and build the given shaders.
    /// @param vertexSourcePath     The path to the vertex shader source.
    /// @param fragmentSourcePath   The path to the fragment shader source.
    ShaderProgram(const char *vertexSourcePath, const char *fragmentSourcePath);

    /// @brief Use/activate the shader.
    void use();

    /// @brief Set the bool value of the given named uniform.
    /// @param name     The name of the uniform.
    /// @param value    The value to set the uniform.
    void setBool(const std::string &name, bool value) const;

    /// @brief Set the int value of the given named uniform.
    /// @param name     The name of the uniform.
    /// @param value    The value to set the uniform.
    void setInt(const std::string &name, int value) const;

    /// @brief Set the float value of the given named uniform.
    /// @param name     The name of the uniform.
    /// @param value    The value to set the uniform.
    void setFloat(const std::string &name, float value) const;

    /// @brief Set the 4x4 matrix value of the given named uniform.
    /// @param name     The name of the uniform.
    /// @param value    The value to set the uniform.
    void setMat4(const std::string &name, const glm::mat4 &value) const;
};
} // namespace ZameEngine
