#include "window.hpp"

// System includes
#include <iostream>

//-----
ZameEngine::Window::Window() : mInitialized(false), mWindow(nullptr)
{
}

//-----
ZameEngine::Window::~Window()
{
    if (mInitialized)
    {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        mInitialized = false;
    }
}

//-----
bool ZameEngine::Window::initialize(unsigned int width, unsigned int height, const std::string &windowName)
{
    if (!glfwInit())
    {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    mInitialized = true;
    mWidth = width;
    mHeight = height;

    return true;
}

//-----
void ZameEngine::Window::startDraw()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-----
void ZameEngine::Window::endDraw()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

//-----
unsigned int ZameEngine::Window::getWidth() const
{
    return mWidth;
}

//-----
unsigned int ZameEngine::Window::getHeight() const
{
    return mHeight;
}

//-----
float ZameEngine::Window::getAspectRatio() const
{
    return static_cast<float>(mHeight) / static_cast<float>(mWidth);
}
