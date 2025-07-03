#include "attack_system.hpp"
#include "attack_component.hpp"
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
        TransformComponent *entityTransform = ComponentRegistry<TransformComponent>::get(entity);
        InputComponent *entityInput = ComponentRegistry<InputComponent>::get(entity);
        AttackComponent *entityAttack = ComponentRegistry<AttackComponent>::get(entity);

        if (entityTransform != nullptr && entityInput != nullptr && entityAttack != nullptr)
        {
            switch (entityAttack->stage)
            {
            case AttackStage::INITIALIZE: {
                if (entityInput->attack())
                {
                    entityAttack->direction =
                        glm::normalize(glm::vec3(entityInput->mouseClickWorldPosition, 0) - entityTransform->position);
                    entityAttack->destination =
                        entityTransform->position + entityAttack->direction * entityAttack->distance;
                    entityAttack->stage = AttackStage::WINDUP;
                }
                break;
            }
            case AttackStage::WINDUP:
                entityAttack->stage = AttackStage::ACTIVE;
                break;
            case AttackStage::ACTIVE: {
                // std::cout << "Before: " << entityTransform->position.x << " " << entityTransform->position.y << "
                // "
                //           << entityTransform->position.z << std::endl;
                float prevDistance = glm::distance(entityTransform->position, entityAttack->destination);

                glm::vec3 nextPosition;
                nextPosition.x =
                    entityTransform->position.x + (entityAttack->direction.x * entityAttack->speed * deltaTime);
                nextPosition.y =
                    entityTransform->position.y + (entityAttack->direction.y * entityAttack->speed * deltaTime);

                float nextDistance = glm::distance(nextPosition, entityAttack->destination);

                if (nextDistance >= prevDistance)
                {
                    entityTransform->position = entityAttack->destination;
                    entityAttack->stage = AttackStage::COOLDOWN;
                }
                else
                {
                    entityTransform->position = nextPosition;
                }

                //  std::cout << "After: " << entityTransform->position.x << " " << entityTransform->position.y << "
                //  "
                //            << entityTransform->position.z << std::endl;
                break;
            }
            case AttackStage::COOLDOWN:
                entityAttack->stage = AttackStage::FINALIZE;
                break;
            case AttackStage::FINALIZE:
                entityAttack->stage = AttackStage::INITIALIZE;
                break;
            default:
                break;
            }
        }
    }
}
