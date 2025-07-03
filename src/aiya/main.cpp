#include "game.hpp"

// Emscripten includes
#include <emscripten.h>

// System includes
#include <chrono>
#include <iostream>

std::unique_ptr<Aiya::Game> gGame;
std::chrono::high_resolution_clock::time_point gLastFrameTime;

void mainLoop()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(currentTime - gLastFrameTime).count();
    gLastFrameTime = currentTime;

    gGame->update(deltaTime);
}

int main()
{
    auto window = std::make_unique<ZameEngine::Window>();
    if (!window->initialize(800, 600, "Game!"))
    {
        return 1;
    }

    auto program = std::make_unique<ZameEngine::ShaderProgram>("shaders/vertex.glsl", "shaders/fragment.glsl");
    auto renderer = std::make_unique<ZameEngine::RenderSystem>(std::move(window), std::move(program));
    auto inputReader = std::make_unique<ZameEngine::InputSystem>(800, 600);
    auto walkSystem = std::make_unique<ZameEngine::WalkSystem>();
    auto attackSystem = std::make_unique<ZameEngine::AttackSystem>();

    gGame = std::make_unique<Aiya::Game>(std::move(inputReader), std::move(walkSystem), std::move(attackSystem),
                                         std::move(renderer));
    gLastFrameTime = std::chrono::high_resolution_clock::now();

    emscripten_set_main_loop(&mainLoop, 0, true);

    return 0;
}