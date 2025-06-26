#pragma once

// ZameEngine includes
#include "entity.hpp"
#include "shader_program.hpp"
#include "texture.hpp"
#include "window.hpp"

// System includes
#include <unordered_map>
#include <vector>

namespace ZameEngine
{
class RenderSystem
{
  public:
    RenderSystem(std::unique_ptr<Window> window, std::unique_ptr<ShaderProgram> program);
    ~RenderSystem();

    void render(std::vector<Entity> &entities);
    unsigned int loadTexture(const std::string &texturePath);

  private:
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<ShaderProgram> mShaderProgram;
    std::unordered_map<unsigned int, Texture> mTextures;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};
} // namespace ZameEngine
