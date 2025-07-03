#include "input_system.hpp"
#include "component_registry.hpp"
#include "input_component.hpp"

#include <iostream>

//-----
bool onKeyDownCallback(int eventType, const EmscriptenKeyboardEvent *keyboardEvent, void *userData)
{
    // std::cout << "Hello, keydown?" << std::endl;

    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    if (system != nullptr)
    {
        return system->onKeyDown(eventType, keyboardEvent);
    }

    return false;
}

//-----
bool onKeyUpCallback(int eventType, const EmscriptenKeyboardEvent *keyboardEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    if (system != nullptr)
    {
        return system->onKeyUp(eventType, keyboardEvent);
    }

    return false;
}

//-----
bool onMouseClickCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    if (system != nullptr)
    {
        return system->onMouseClick(eventType, mouseEvent);
    }

    return false;
}

//-----
bool onMouseDownCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    if (system != nullptr)
    {
        return system->onMouseDown(eventType, mouseEvent);
    }

    return false;
}

//-----
bool onMouseUpCallback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    ZameEngine::InputSystem *system = static_cast<ZameEngine::InputSystem *>(userData);
    if (system != nullptr)
    {
        return system->onMouseUp(eventType, mouseEvent);
    }

    return false;
}

//-----
ZameEngine::InputSystem::InputSystem(unsigned int width, unsigned int height)
    : mWindowWidth(width), mWindowHeight(height), mButtonStates(), mMousePositionClick(), mMousePositionDown(),
      mMousePositionUp()
{
    EMSCRIPTEN_RESULT result;
    result = emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, onKeyDownCallback);
    result = emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, onKeyUpCallback);

    result = emscripten_set_click_callback("#canvas", this, 1, onMouseClickCallback);
    result = emscripten_set_mousedown_callback("#canvas", this, 1, onMouseDownCallback);
    result = emscripten_set_mouseup_callback("#canvas", this, 1, onMouseUpCallback);
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
            entityInput->buttonField = mButtonStates;

            if (mButtonStates.get(Button::MOUSE_CLICK_LEFT) || mButtonStates.get(Button::MOUSE_CLICK_MIDDLE) ||
                mButtonStates.get(Button::MOUSE_CLICK_RIGHT))
            {
                entityInput->mouseClickWorldPosition = screenToWorldPoint(mMousePositionClick);
            }
        }
    }

    // Reset MOUSE_CLICK states
    if (mButtonStates.get(Button::MOUSE_CLICK_LEFT))
    {
        mButtonStates.unset(Button::MOUSE_CLICK_LEFT);
    }

    if (mButtonStates.get(Button::MOUSE_CLICK_MIDDLE))
    {
        mButtonStates.unset(Button::MOUSE_CLICK_MIDDLE);
    }

    if (mButtonStates.get(Button::MOUSE_CLICK_RIGHT))
    {
        mButtonStates.unset(Button::MOUSE_CLICK_RIGHT);
    }
}

//-----
bool ZameEngine::InputSystem::onKeyDown(int eventType, const EmscriptenKeyboardEvent *keyboardEvent)
{
    // std::cout << "Key down: " << keyboardEvent->key << " " << keyboardEvent->code << std::endl;
    // std::cout << "<BEFORE> ButtonStates: " << std::hex << mButtonStates << std::endl;

    mButtonStates.set(keyToButton(keyboardEvent->code));

    // std::cout << "<AFTER> ButtonStates: " << std::hex << mButtonStates << std::endl;

    return false;
}

//-----
bool ZameEngine::InputSystem::onKeyUp(int eventType, const EmscriptenKeyboardEvent *keyboardEvent)
{
    // std::cout << "Key up: " << keyboardEvent->key << " " << keyboardEvent->code << std::endl;

    mButtonStates.unset(keyToButton(keyboardEvent->code));

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseClick(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    // std::cout << "Mouse click: " << mouseEvent->button << std::endl;

    mButtonStates.set(mouseToButton(mouseEvent->button, true));

    // Convert canvas mouse position to world position

    mMousePositionClick = glm::vec2(mouseEvent->targetX, mouseEvent->targetY);

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseDown(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    // std::cout << "<BEFORE> ButtonStates: " << std::hex << mButtonStates << std::endl;

    mButtonStates.set(mouseToButton(mouseEvent->button, false));

    // std::cout << "<AFTER> ButtonStates: " << std::hex << mButtonStates << std::endl;
    mMousePositionDown = glm::vec2(mouseEvent->targetX, mouseEvent->targetY);

    return false;
}

//-----
bool ZameEngine::InputSystem::onMouseUp(int eventType, const EmscriptenMouseEvent *mouseEvent)
{
    // std::cout << "<BEFORE> ButtonStates: " << std::hex << mButtonStates << std::endl;

    mButtonStates.unset(mouseToButton(mouseEvent->button, false));

    // std::cout << "<AFTER> ButtonStates: " << std::hex << mButtonStates << std::endl;
    mMousePositionUp = glm::vec2(mouseEvent->targetX, mouseEvent->targetY);

    return false;
}

//-----
ZameEngine::Button ZameEngine::InputSystem::keyToButton(const std::string &keyCode)
{
    if (keyCode == "KeyW")
    {
        return Button::KEY_W;
    }
    else if (keyCode == "KeyA")
    {
        return Button::KEY_A;
    }
    else if (keyCode == "KeyS")
    {
        return Button::KEY_S;
    }
    else if (keyCode == "KeyD")
    {
        return Button::KEY_D;
    }
    else
    {
        return Button::UNKNOWN;
    }
}

//-----
ZameEngine::Button ZameEngine::InputSystem::mouseToButton(unsigned short mouseCode, bool click)
{
    switch (mouseCode)
    {
    case 0:
        return click ? Button::MOUSE_CLICK_LEFT : Button::MOUSE_DOWN_LEFT;
    case 1:
        return click ? Button::MOUSE_CLICK_MIDDLE : Button::MOUSE_DOWN_MIDDLE;
    case 2:
        return click ? Button::MOUSE_CLICK_RIGHT : Button::MOUSE_DOWN_RIGHT;
    default:
        return Button::UNKNOWN;
    }
}

//-----
glm::vec2 ZameEngine::InputSystem::screenToWorldPoint(const glm::vec2 &screenPoint)
{
    float windowRatio = static_cast<float>(mWindowHeight) / static_cast<float>(mWindowWidth);
    float halfWindowWidth = static_cast<float>(mWindowWidth) / 2.0f;
    float halfWindowHeight = static_cast<float>(mWindowHeight) / 2.0f;

    glm::vec2 worldPoint;

    worldPoint.x = (screenPoint.x - halfWindowWidth) * (10.0f / halfWindowWidth);
    worldPoint.y = -1 * (screenPoint.y - halfWindowHeight) * (10.0f / halfWindowHeight) * windowRatio;

    std::cout << "Screen point: " << screenPoint.x << " " << screenPoint.y << "\nWorld point: " << worldPoint.x << " "
              << worldPoint.y << std::endl;

    return worldPoint;
}