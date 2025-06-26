#pragma once

// ZameEngine includes
#include "entity.hpp"

// System includes
#include <vector>

namespace ZameEngine
{
class WalkSystem
{
  public:
    WalkSystem();
    ~WalkSystem();

    void update(float deltaTime, const std::vector<Entity> &entities);
};
} // namespace ZameEngine
