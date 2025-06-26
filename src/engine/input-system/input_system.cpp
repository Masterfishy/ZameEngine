#include "input_system.hpp"
#include "component_registry.hpp"
#include "input_codes.hpp"
#include "input_component.hpp"

#include <iostream>

//-----
bool onKeyDownCallback(int eventType, const EmscriptenKeyboardEvent *keyboardEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    return system->onKeyDown(eventType, keyboardEvent);
}

//-----
bool onKeyUpCallback(int eventType, const EmscriptenKeyboardEvent *keyboardEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    return system->onKeyUp(eventType, keyboardEvent);
}

//-----
bool onMouseClickCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    return system->onMouseClick(eventType, mouseEvent);
}

//-----
bool onMouseDownCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    return system->onMouseDown(eventType, mouseEvent);
}

//-----
bool onMouseUpCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    return system->onMouseUp(eventType, mouseEvent);
}

//-----
ZameEngine::InputSystem::InputSystem() : mInputState(), mMousePositionClick(), mMousePositionDown(), mMousePositionUp()
{
    EMSCRIPTEN_RESULT result;
    result = emscripten_set_keydown_callback("#canvas", this, 1, onKeyDownCallback);
    result = emscripten_set_keyup_callback("#canvas", this, 1, onKeyUpCallback);
    result = emscripten_set_click_callback("#canvas", this, 1, onMouseClickCallback);
    result = emscripten_set_mousedown_callback("#canvas", this, 1, onMouseDownCallback);
    result = emscripten_set_mouseup_callback("#canvas", this, 1, onMouseUpCallback);

    mInputState = {{InputCode::KEY_W, false},
                   {InputCode::KEY_A, false},
                   {InputCode::KEY_S, false},
                   {InputCode::KEY_D, false},
                   {InputCode::MOUSE_CLICK_LEFT, false}};
}

//-----
ZameEngine::InputSystem::~InputSystem()
{
}

//-----
void ZameEngine::InputSystem::update(const std::vector<Entity> &entities)
{
    // static float totalTime = 0;
    // if (totalTime > 5)
    // {
    //     for (const auto &inputState : mInputState)
    //     {
    //         std::cout << "Key: " << inputState.first << " State: " << inputState.second << std::endl;
    //     }

    //     totalTime = 0;
    // }
    // else
    // {
    //     totalTime += deltaTime;
    // }
    // std::cout << "Total Time: " << totalTime << std::endl;

    for (const Entity &entity : entities)
    {
        InputComponent *entityInput = ComponentRegistry<InputComponent>::get(entity);
        if (entityInput != nullptr)
        {
            for (const auto &inputState : mInputState)
            {
                const auto &entityInputStateIter = entityInput->keyStates.find(inputState.first);
                if (entityInputStateIter != entityInput->keyStates.end())
                {
                    // std::cout << "Set key: " << inputState.first << " to " << inputState.second
                    //           << " for entity: " << entity.getId() << std::endl;
                    entityInputStateIter->second = inputState.second;
                }
            }

            entityInput->mousePosition = mMousePositionClick;
        }
    }

    // Reset MOUSE_CLICK states
    const auto &mouseClickLeft = mInputState.find(InputCode::MOUSE_CLICK_LEFT);
    if (mouseClickLeft != mInputState.end() && mouseClickLeft->second)
    {
        mouseClickLeft->second = false;
        // std::cout << mouseClickLeft->first << " state: " << mouseClickLeft->second << std::endl;
    }

    const auto &mouseClickMiddle = mInputState.find(InputCode::MOUSE_CLICK_MIDDLE);
    if (mouseClickMiddle != mInputState.end() && mouseClickMiddle->second)
    {
        mouseClickMiddle->second = false;
    }

    const auto &mouseClickRight = mInputState.find(InputCode::MOUSE_CLICK_RIGHT);
    if (mouseClickRight != mInputState.end() && mouseClickRight->second)
    {
        mouseClickRight->second = false;
    }
}

//-----
bool ZameEngine::InputSystem::onKeyDown(int eventType, const EmscriptenKeyboardEvent *keyboardEvent)
{
    // std::cout << "Key down: " << keyboardEvent->key << " " << keyboardEvent->code << std::endl;

    const auto &inputStateIter = mInputState.find(keyboardEvent->code);
    if (inputStateIter != mInputState.end())
    {
        inputStateIter->second = true;
    }

    return false;
}

//-----
bool ZameEngine::InputSystem::onKeyUp(int eventType, const EmscriptenKeyboardEvent *keyboardEvent)
{
    // std::cout << "Key up: " << keyboardEvent->key << " " << keyboardEvent->code << std::endl;

    const auto &inputStateIter = mInputState.find(keyboardEvent->code);
    if (inputStateIter != mInputState.end())
    {
        inputStateIter->second = false;
    }

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseClick(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    std::string mouseCode = "MOUSE_CLICK_" + std::to_string(mouseEvent->button);
    const auto &inputStateIter = mInputState.find(mouseCode);
    if (inputStateIter != mInputState.end())
    {
        inputStateIter->second = true;
        // std::cout << mouseCode << ": " << mouseEvent->button << " state: " << inputStateIter->second << std::endl;
    }

    // std::cout << "target " << mouseEvent->targetX << " " << mouseEvent->targetY << std::endl;
    // std::cout << "client " << mouseEvent->clientX << " " << mouseEvent->clientY << std::endl;
    // std::cout << "screen " << mouseEvent->screenX << " " << mouseEvent->screenY << std::endl;

    // Convert canvas mouse position to world position

    mMousePositionClick = glm::vec2(mouseEvent->targetX, mouseEvent->targetY);

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseDown(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    std::string mouseCode = "MOUSE_" + std::to_string(mouseEvent->button);
    const auto &inputStateIter = mInputState.find(mouseCode);
    if (inputStateIter != mInputState.end())
    {
        inputStateIter->second = true;
        // std::cout << mouseCode << ": " << mouseEvent->button << " state: " << inputStateIter->second << std::endl;
    }

    mMousePositionDown = glm::vec2(mouseEvent->clientX, mouseEvent->clientY);

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseUp(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    std::string mouseCode = "MOUSE_" + std::to_string(mouseEvent->button);
    const auto &inputStateIter = mInputState.find(mouseCode);
    if (inputStateIter != mInputState.end())
    {
        inputStateIter->second = false;
        // std::cout << mouseCode << ": " << mouseEvent->button << " state: " << inputStateIter->second << std::endl;
    }

    mMousePositionUp = glm::vec2(mouseEvent->clientX, mouseEvent->clientY);

    return false;
}
