#pragma once

// ZameEngine includes
#include "input_codes.hpp"

// GLM includes
#include <glm/glm.hpp>

// System includes
#include <iostream>
#include <string>
#include <unordered_map>

namespace ZameEngine
{
struct InputComponent
{
  public:
    glm::vec2 mouseClickWorldPosition;
    ButtonField buttonField;

    unsigned int up() const
    {
        return getButtonState(upButtonBinding);
    }

    InputComponent &up(Button button)
    {
        return setButtonState(upButtonBinding, button);
    }

    unsigned int down() const
    {
        return getButtonState(downButtonBinding);
    }

    InputComponent &down(Button button)
    {
        return setButtonState(downButtonBinding, button);
    }

    unsigned int left() const
    {
        return getButtonState(leftButtonBinding);
    }

    InputComponent &left(Button button)
    {
        return setButtonState(leftButtonBinding, button);
    }

    unsigned int right() const
    {
        return getButtonState(rightButtonBinding);
    }

    InputComponent &right(Button button)
    {
        return setButtonState(rightButtonBinding, button);
    }

    unsigned int attack() const
    {
        return getButtonState(attackButtonBinding);
    }

    InputComponent &attack(Button button)
    {
        return setButtonState(attackButtonBinding, button);
    }

  private:
    Button upButtonBinding;
    Button downButtonBinding;
    Button leftButtonBinding;
    Button rightButtonBinding;
    Button attackButtonBinding;

    bool getButtonState(Button button) const
    {
        return buttonField.get(button);
    }

    InputComponent &setButtonState(Button &buttonBinding, Button newButton)
    {
        // Reset the old button state
        buttonField.unset(buttonBinding);

        // Set the new button state
        buttonBinding = newButton;
        buttonField.set(buttonBinding);

        return *this;
    }
};
} // namespace ZameEngine
