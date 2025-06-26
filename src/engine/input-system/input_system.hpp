#pragma once

#include "entity.hpp"

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
    InputSystem();
    ~InputSystem();

    bool onKeyDown(int eventType, const EmscriptenKeyboardEvent *keyboardEvent);
    bool onKeyUp(int eventType, const EmscriptenKeyboardEvent *keyboardEvent);

    bool onMouseClick(int eventType, const EmscriptenMouseEvent *mouseEvent);
    bool onMouseDown(int eventType, const EmscriptenMouseEvent *mouseEvent);
    bool onMouseUp(int eventType, const EmscriptenMouseEvent *mouseEvent);

    void update(const std::vector<Entity> &entities);

  private:
    std::unordered_map<std::string, bool> mInputState;

    glm::vec2 mMousePositionClick;
    glm::vec2 mMousePositionDown;
    glm::vec2 mMousePositionUp;
};
} // namespace ZameEngine
