#pragma once

#include <glm/glm.hpp> // glm::vec3

namespace ZameEngine
{
struct TransformComponent
{
  public:
    glm::vec3 position;
    glm::vec3 rotation;
};
} // namespace ZameEngine
