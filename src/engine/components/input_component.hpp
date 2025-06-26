#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <unordered_map>

namespace ZameEngine
{
struct InputComponent
{
  public:
    glm::vec2 mousePosition;
    std::unordered_map<std::string, bool> keyStates;

    bool up() const
    {
        return getInputState(upKeyCode);
    }

    InputComponent &up(const std::string &keyCode)
    {
        return setInputState(&upKeyCode, keyCode);
    }

    bool down() const
    {
        return getInputState(downKeyCode);
    }

    InputComponent &down(const std::string &keyCode)
    {
        return setInputState(&downKeyCode, keyCode);
    }

    bool left() const
    {
        return getInputState(leftKeyCode);
    }

    InputComponent &left(const std::string &keyCode)
    {
        return setInputState(&leftKeyCode, keyCode);
    }

    bool right() const
    {
        return getInputState(rightKeyCode);
    }

    InputComponent &right(const std::string &keyCode)
    {
        return setInputState(&rightKeyCode, keyCode);
    }

    bool attack() const
    {
        return getInputState(attackKeyCode);
    }

    InputComponent &attack(const std::string &keyCode)
    {
        return setInputState(&attackKeyCode, keyCode);
    }

  private:
    std::string upKeyCode;
    std::string downKeyCode;
    std::string leftKeyCode;
    std::string rightKeyCode;
    std::string attackKeyCode;

    bool getInputState(const std::string &keyCode) const
    {
        const auto &keyStateIter = keyStates.find(keyCode);
        if (keyStateIter != keyStates.end())
        {
            return keyStateIter->second;
        }

        return false;
    }

    InputComponent &setInputState(std::string *keyCode, const std::string &newCode)
    {
        // std::cout << "Setting: " << *keyCode << " to: " << newCode << std::endl;
        if (keyCode != nullptr)
        {
            keyStates.erase(*keyCode);

            *keyCode = newCode;
            keyStates[*keyCode] = false;
        }

        return *this;
    }
};
} // namespace ZameEngine
