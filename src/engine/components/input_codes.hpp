#pragma once

#include <string>

namespace ZameEngine
{
enum Button
{
    UNKNOWN = 0,

    // Keys
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,

    // Mouse
    MOUSE_DOWN_LEFT,
    MOUSE_DOWN_MIDDLE,
    MOUSE_DOWN_RIGHT,

    MOUSE_CLICK_LEFT,
    MOUSE_CLICK_MIDDLE,
    MOUSE_CLICK_RIGHT
};

struct ButtonField
{
    unsigned int mField = 0;

    void set(Button button)
    {
        mField |= 1 << button;
    }

    void unset(Button button)
    {
        mField &= ~(1 << button);
    }

    unsigned int get(Button button) const
    {
        return (mField & (1 << button)) >> button;
    }
};
} // namespace ZameEngine
