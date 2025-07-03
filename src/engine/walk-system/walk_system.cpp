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
            //           << " y:" << transform->position.y << "Input: " << entityInput->up() << " " <<
            //           entityInput->down()
            //           << " " << entityInput->left() << " " << entityInput->right() << std::endl;

            transform->position.x +=
                entityWalk->speed * deltaTime * static_cast<signed int>(entityInput->right() - entityInput->left());
            transform->position.y +=
                entityWalk->speed * deltaTime * static_cast<signed int>(entityInput->up() - entityInput->down());

            // std::cout << "Z Pos: " << transform->position.z << " X Pos: " << transform->position.x << std::endl;

            // std::cout << "X Movement: " << entityInput->up() - entityInput->down() << std::endl;
            // std::cout << "Y Movement: " << entityInput->right() - entityInput->left() << std::endl;
        }
    }
}
