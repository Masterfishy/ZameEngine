#include "input_component.hpp"

#include <gtest/gtest.h>

TEST(InputComponentTest, test_ButtonSetAndGet)
{
    ZameEngine::InputComponent comp;

    EXPECT_EQ(comp.up(), 0);

    comp.up(ZameEngine::Button::KEY_W);

    EXPECT_EQ(comp.up(), 1);

    std::cout << "Size of bool: " << sizeof(bool) << std::endl;
}
