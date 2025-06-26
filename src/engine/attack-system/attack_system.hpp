#pragma once

#include "entity.hpp"

#include <vector>

namespace ZameEngine
{
class AttackSystem
{
  public:
    AttackSystem();
    ~AttackSystem();

    void update(float deltaTime, const std::vector<Entity> &entities);
};
} // namespace ZameEngine