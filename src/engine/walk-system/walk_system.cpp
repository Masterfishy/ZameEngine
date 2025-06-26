#include "walk_system.hpp"
#include "component_registry.hpp"
#include "input_component.hpp"
#include "transform_component.hpp"
#include "walk_component.hpp"

//-----
ZameEngine::WalkSystem::WalkSystem()
{
}

//-----
ZameEngine::WalkSystem::~WalkSystem()
{
}

//-----
void ZameEngine::WalkSystem::update(float deltaTime, const std::vector<ZameEngine::Entity> &entities)
{
    for (const Entity &entity : entities)
    {
        InputComponent *entityInput = ComponentRegistry<InputComponent>::get(entity);
        TransformComponent *transform = ComponentRegistry<TransformComponent>::get(entity);
        WalkComponent *entityWalk = ComponentRegistry<WalkComponent>::get(entity);

        if (entityInput != nullptr && transform != nullptr && entityWalk != nullptr)
        {
            // std::cout << "Entity: " << entity.getId() << " position= x:" << transform->position.x
            //           << " y:" << transform->position.y << "Input: " << entityInput->up() << " "
            //           << entityInput->down() << " " << entityInput->left() << " " << entityInput->right()
            //           << std::endl;

            transform->position.x += entityWalk->walkSpeed * deltaTime * (entityInput->right() - entityInput->left());
            transform->position.y += entityWalk->walkSpeed * deltaTime * (entityInput->up() - entityInput->down());
        }
    }
}
