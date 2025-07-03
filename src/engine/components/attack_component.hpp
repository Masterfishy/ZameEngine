#pragma once

#include <glm/glm.hpp>

namespace ZameEngine
{
enum AttackStage
{
    INITIALIZE,
    WINDUP,
    ACTIVE,
    COOLDOWN,
    FINALIZE
};

struct AttackComponent
{
    float speed;
    float distance;
    AttackStage stage;
    glm::vec3 direction;
    glm::vec3 destination;
};
} // namespace ZameEngine
