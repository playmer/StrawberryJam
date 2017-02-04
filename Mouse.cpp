
#include <iostream>

#include "glfw/include/GLFW/glfw3.h"

#include "Engine.hpp"
#include "Mouse.hpp"


// Mouse related event strings.
namespace Events
{
  const std::string MousePress{ "MousePress" };
  const std::string MouseRelease{ "MouseRelease" };
  const std::string MousePersist{ "MousePersist" };
  const std::string MouseScroll{ "MouseScroll" };
  const std::string MouseMove{ "MouseMove" };
}

Mouse::Mouse(Engine *aEngine) : mEngine(aEngine)
{
  for (glm::i16 i = 0; i < 3; ++i)
  {
    Key *key = &mButtons[i];

    // Default everything to Up.
    key->mPreviousState = key->mCurrentState = ButtonState::Up;
  }

  glfwSetMouseButtonCallback(mEngine->mWindow.mWindow, mouse_button_callback);
  glfwSetCursorEnterCallback(mEngine->mWindow.mWindow, cursor_enter_callback);
  glfwSetCursorPosCallback(mEngine->mWindow.mWindow, cursor_position_callback); 
  glfwSetScrollCallback(mEngine->mWindow.mWindow, scroll_callback);
}

Mouse::~Mouse()
{
}

void Mouse::cursor_position_callback(GLFWwindow* aWindow, double aX, double aY)
{
  Surface *surface = (Surface*)glfwGetWindowUserPointer(aWindow);
  
  glm::i32vec2 move{ (int)aX, (int)aY };
  surface->mEngine->mMouse.UpdateMovement(move);
}

void Mouse::cursor_enter_callback(GLFWwindow* aWindow, int aEntered)
{
  Surface *surface = (Surface*)glfwGetWindowUserPointer(aWindow);
  surface->mEngine->mMouse;
  if (aEntered)
  {
    // The cursor entered the client area of the window
  }
  else
  {
    // The cursor left the client area of the window
  }
}
void Mouse::mouse_button_callback(GLFWwindow* aWindow, int aButton, int aAction, int aMods)
{
  Surface *surface = (Surface*)glfwGetWindowUserPointer(aWindow);
  surface->mEngine->mMouse.UpdateButton((MouseButton)aButton, aAction);
}
void Mouse::scroll_callback(GLFWwindow* aWindow, double aX, double aY)
{
  Surface *surface = (Surface*)glfwGetWindowUserPointer(aWindow);
  surface->mEngine->mMouse;
}


// Sends out persist events mostly.
void Mouse::Update()
{
  MouseEvent event;
  event.mMouse = this;

  for (glm::u32 i = 0; i < static_cast<char>(3); ++i)
  {
    if (IsButtonDown(static_cast<MouseButton>(i)) && WasButtonDown(static_cast<MouseButton>(i)))
    {
      event.mButton = static_cast<MouseButton>(i);

      SendEvent(Events::MousePersist, &event);
    }

    mButtons[i].mPreviousState = mButtons[i].mCurrentState;
  }
}


void Mouse::UpdateMovement(glm::i32vec2 aMovement)
{
  mPosition = aMovement;

  MouseEvent event;
  event.mMouse = this;
  event.mPosition = aMovement;
  event.mDown = false;

  SendEvent(Events::MouseMove, &event);
}

void Mouse::UpdateButton(MouseButton aButton, int aAction)
{
  size_t index = static_cast<size_t>(aButton);

  printf("UpdateButton\n");

  // Key got resent.
  if ((IsButtonDown(aButton) == (aAction == GLFW_PRESS)) ||
      (aAction == GLFW_REPEAT))
  {
    mButtons[index].mCurrentState = ButtonState::Persist;
    return;
  }

  bool aDown = (aAction == GLFW_PRESS) ? true : false;

  mButtons[index].mPreviousState = mButtons[index].mCurrentState;

  mButtons[index].mCurrentState = aDown ? ButtonState::Pressed : ButtonState::Released;

  const std::string *state;

  // Key has been pressed.
  if (aDown)
  {
    state = &Events::MousePress;
  }
  // Key has been released
  else
  {
    state = &Events::MouseRelease;
  }

  MouseEvent mouseEvent;
  mouseEvent.mPosition = mPosition;
  mouseEvent.mButton = aButton;
  mouseEvent.mMouse = this;

  SendEvent(*state, &mouseEvent);
}
