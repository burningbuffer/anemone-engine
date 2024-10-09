#include "window.hpp"
#include "../logger/logger.hpp"


Window::Window(){}
Window::~Window(){}

bool Window::CreateWindow(const char *windowName, int w, int h)
{
    this->mWindowName = windowName;
    this->mWindowWidth = w;
    this->mWindowHeight = h;

    this->mAspectRatio = static_cast<float>(w) / h;

    return InitGLFW();
}

bool Window::InitGLFW()
{
    if (!glfwInit())
    {
        Logger::Err("Error Initializing GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mWindowName, nullptr, nullptr);
    
    if (!mWindow)
    {
        Logger::Err("Error Creating GLFW Window.");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);

    if (glewInit() != GLEW_OK)
    {
        Logger::Err("Error Initializing GLEW.");
        return false;
    }

    GLint GLMajorVersion = 0;
	GLint GLMinorVersion = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
	std::cout << "OpenGL Version  : " << GLMajorVersion << "." << GLMinorVersion << std::endl;
	std::cout << "OpenGL Vendor   : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version  : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

GLFWwindow* Window::GetWindow()
{
    return mWindow;
}

void Window::RenderClear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::RenderPresent()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void Window::DestroyWindow()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}