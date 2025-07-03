#pragma once

// Emscripten includes
#include <GLFW/glfw3.h>

// System includes
#include <string>

namespace ZameEngine
{
class Window
{
  public:
    Window();
    ~Window();

    bool initialize(unsigned int width, unsigned int height, const std::string &windowName);
    void startDraw();
    void endDraw();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    float getAspectRatio() const;

  private:
    bool mInitialized;
    GLFWwindow *mWindow;

    unsigned int mWidth;
    unsigned int mHeight;
};
} // namespace ZameEngine
