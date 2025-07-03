#pragma once

// ZameEngine includes
#include "entity.hpp"
#include "input_codes.hpp"

// Emscripten includes
#include <emscripten/html5.h>

// GLM includes
#include <glm/glm.hpp>

// System includes
#include <string>
#include <unordered_map>
#include <vector>

namespace ZameEngine
{

class InputSystem
{
  public:
    InputSystem(unsigned int width, unsigned int height);
    ~InputSystem();

    bool onKeyDown(int eventType, const EmscriptenKeyboardEvent *keyboardEvent);
    bool onKeyUp(int eventType, const EmscriptenKeyboardEvent *keyboardEvent);

    bool onMouseClick(int eventType, const EmscriptenMouseEvent *mouseEvent);
    bool onMouseDown(int eventType, const EmscriptenMouseEvent *mouseEvent);
    bool onMouseUp(int eventType, const EmscriptenMouseEvent *mouseEvent);

    void update(const std::vector<Entity> &entities);

  private:
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;

    ButtonField mButtonStates;

    glm::vec2 mMousePositionClick;
    glm::vec2 mMousePositionDown;
    glm::vec2 mMousePositionUp;

    Button keyToButton(const std::string &keyCode);
    Button mouseToButton(unsigned short mouseCode, bool click);

    glm::vec2 screenToWorldPoint(const glm::vec2 &screenPoint);
};
} // namespace ZameEngine
