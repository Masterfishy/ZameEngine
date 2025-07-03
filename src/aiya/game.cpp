#include "game.hpp"

// ZameEngine includes
#include <attack_component.hpp>
#include <component_registry.hpp>
#include <input_codes.hpp>
#include <input_component.hpp>
#include <sprite_component.hpp>
#include <transform_component.hpp>
#include <walk_component.hpp>

// System include
#include <iostream>

//-----
Aiya::Game::Game(std::unique_ptr<ZameEngine::InputSystem> inputReader,
                 std::unique_ptr<ZameEngine::WalkSystem> walkSystem,
                 std::unique_ptr<ZameEngine::AttackSystem> attackSystem,
                 std::unique_ptr<ZameEngine::RenderSystem> renderer)
    : mInputReader(std::move(inputReader)), mWalkSystem(std::move(walkSystem)), mAttackSystem(std::move(attackSystem)),
      mRenderer(std::move(renderer)), mEntities()
{
    unsigned int containerTextureId = mRenderer->loadTexture("textures/container.jpg");

    ZameEngine::Entity e1(1);
    ZameEngine::Entity e2(2);
    ZameEngine::Entity e3(3);

    ZameEngine::ComponentRegistry<ZameEngine::TransformComponent>::add(
        e1, {.position = {-1.0f, -1.0f, 0.0f}, .rotation = {0.0f, 0.0f, 0.0f}});
    ZameEngine::ComponentRegistry<ZameEngine::TransformComponent>::add(
        e2, {.position = {0.0f, 0.0f, 0.0f}, .rotation = {0.0f, 0.0f, 0.0f}});
    ZameEngine::ComponentRegistry<ZameEngine::TransformComponent>::add(
        e3, {.position = {0.0f, 1.0f, 0.0f}, .rotation = {0.0f, 0.0f, 0.0f}});

    ZameEngine::ComponentRegistry<ZameEngine::SpriteComponent>::add(e1, {.textureId = containerTextureId});
    ZameEngine::ComponentRegistry<ZameEngine::SpriteComponent>::add(e2, {.textureId = containerTextureId});
    ZameEngine::ComponentRegistry<ZameEngine::SpriteComponent>::add(e3, {.textureId = containerTextureId});

    ZameEngine::InputComponent inputComponent;
    inputComponent.up(ZameEngine::Button::KEY_W)
        .down(ZameEngine::Button::KEY_S)
        .left(ZameEngine::Button::KEY_A)
        .right(ZameEngine::Button::KEY_D)
        .attack(ZameEngine::Button::MOUSE_CLICK_LEFT);
    ZameEngine::ComponentRegistry<ZameEngine::InputComponent>::add(e1, inputComponent);

    ZameEngine::ComponentRegistry<ZameEngine::WalkComponent>::add(e1, {.speed = 10});
    ZameEngine::ComponentRegistry<ZameEngine::AttackComponent>::add(e1, {.speed = 50,
                                                                         .distance = 7,
                                                                         .stage = ZameEngine::AttackStage::INITIALIZE,
                                                                         .direction = glm::vec3(0.0f),
                                                                         .destination = glm::vec3(0.0f)});

    mEntities.push_back(std::move(e1));
    mEntities.push_back(std::move(e2));
    mEntities.push_back(std::move(e3));
}

//-----
Aiya::Game::~Game()
{
}

//-----
void Aiya::Game::update(float deltaTime)
{
    // std::cout << "Game update!" << std::endl;

    if (mInputReader)
    {
        mInputReader->update(mEntities);
    }

    if (mWalkSystem)
    {
        mWalkSystem->update(deltaTime, mEntities);
    }

    if (mAttackSystem)
    {
        mAttackSystem->update(deltaTime, mEntities);
    }

    if (mRenderer)
    {
        mRenderer->render(mEntities);
    }
}
