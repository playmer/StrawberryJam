#include <iostream>
#include "GL/glew.h"
#include <glfw/include/GLFW/glfw3.h>

#include "Surface.hpp"

Surface::Surface(const char * aTitle, Engine *aEngine)
  : mEngine(aEngine)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  mWindow = glfwCreateWindow(1280, 720, aTitle, nullptr, nullptr);

  if (mWindow == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    std::terminate();
  }

  glfwMakeContextCurrent(mWindow);
  glfwSetWindowUserPointer(mWindow, this);

  glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
  glViewport(0, 0, mWidth, mHeight);

  glewExperimental = GL_TRUE;
  glewInit();
}

Surface::~Surface()
{
  glfwTerminate();
}

void Surface::Update(double aDt)
{
  glfwPollEvents();
  glfwSwapBuffers(mWindow);
}
