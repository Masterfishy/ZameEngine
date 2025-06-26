#pragma once

// ZameEngine includes
#include <attack_system.hpp>
#include <input_system.hpp>
#include <render_system.hpp>
#include <walk_system.hpp>

// System includes
#include <memory>

namespace Aiya
{
class Game
{
  public:
    Game(std::unique_ptr<ZameEngine::InputSystem> inputReader, std::unique_ptr<ZameEngine::WalkSystem> walkSystem,
         std::unique_ptr<ZameEngine::AttackSystem> attackSystem, std::unique_ptr<ZameEngine::RenderSystem> renderer);
    ~Game();

    void update(float deltaTime);

  private:
    std::unique_ptr<ZameEngine::InputSystem> mInputReader;
    std::unique_ptr<ZameEngine::RenderSystem> mRenderer;

    std::unique_ptr<ZameEngine::AttackSystem> mAttackSystem;
    std::unique_ptr<ZameEngine::WalkSystem> mWalkSystem;

    std::vector<ZameEngine::Entity> mEntities;
};
} // namespace Aiya