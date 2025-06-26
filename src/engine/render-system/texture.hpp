#pragma once

namespace ZameEngine
{
class Texture
{
  public:
    /// @brief The ID of the texture.
    unsigned int ID;

    /// @brief Construct a new GL Texture from the given image path.
    /// @param textureSourcePath The path to the texture resource.
    Texture(const char *textureSourcePath);
};
} // namespace ZameEngine
