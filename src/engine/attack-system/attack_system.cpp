#include "attack_system.hpp"
#include "component_registry.hpp"
#include "input_component.hpp"
#include "transform_component.hpp"

//-----
ZameEngine::AttackSystem::AttackSystem()
{
}

//-----
ZameEngine::AttackSystem::~AttackSystem()
{
}

//-----
void ZameEngine::AttackSystem::update(float deltaTime, const std::vector<Entity> &entities)
{
    for (const Entity &entity : entities)
    {
        TransformComponent *transform = ComponentRegistry<TransformComponent>::get(entity);
        InputComponent *entityInput = ComponentRegistry<InputComponent>::get(entity);

        if (transform != nullptr && entityInput != nullptr)
        {
            if (entityInput->attack())
            {
                // std::cout << "Before: " << transform->position.x << " " << transform->position.y << " "
                //           << transform->position.z << std::endl;

                transform->position = glm::vec3(entityInput->mousePosition, transform->position.z);
                // std::cout << "After: " << transform->position.x << " " << transform->position.y << " "
                //           << transform->position.z << std::endl;
            }
        }
    }
}
