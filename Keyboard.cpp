#include <iostream>

#include "glfw/include/GLFW/glfw3.h"


#include "Engine.hpp"
#include "Keyboard.hpp"
#include "Surface.hpp"

namespace Events
{
  const std::string KeyPress{ "KeyPress" };
  const std::string KeyRelease{ "KeyRelease" };
  const std::string KeyPersist{ "KeyPersist" };
}

void Keyboard::key_callback(GLFWwindow *aWindow, 
                            int aKey, 
                            int aScancode, 
                            int aAction, 
                            int aMods)
{
  Surface *surface = (Surface*)glfwGetWindowUserPointer(aWindow);
  surface->mEngine->mKeyboard.UpdateKey(aKey, aAction);
}

Keyboard::Keyboard(Engine *aEngine) : mEngine(aEngine)
{

  for (glm::i16 i = 0; i < 256; ++i)
  {
    Key *key = &mKeys[i];

    key->mPreviousState = key->mCurrentState = ButtonState::Up;
  }

  mShift = false;
  mControl = false;
  mAlt = false;


  glfwSetKeyCallback(mEngine->mWindow.mWindow, key_callback);
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
  KeyEvent event;
  event.mKeyboard = this;

  for (int i = 0; i < 400; ++i)
  {
    if (IsKeyDown(i) && WasKeyDown(i))
    {
      event.mKey = i;

      SendEvent(Events::KeyPersist, &event);
    }

    mKeys[i].mPreviousState = mKeys[i].mCurrentState;
  }
}

void Keyboard::UpdateKey(char aKey, int aAction)
{
  size_t index = static_cast<size_t>(aKey);

  // Key got resent.
  if ((IsKeyDown(aKey) == (aAction == GLFW_PRESS)) || 
      (aAction == GLFW_REPEAT))
  {
    mKeys[aKey].mCurrentState = ButtonState::Persist;
    return;
  }

  bool aDown = (aAction == GLFW_PRESS) ? true : false;

  mKeys[aKey].mPreviousState = mKeys[aKey].mCurrentState;

  mKeys[aKey].mCurrentState = aDown ? ButtonState::Pressed : ButtonState::Released;

  const std::string *state;

  // Key has been pressed.
  if (aDown)
  {
    state = &Events::KeyPress;
  }
  // Key has been released
  else
  {
    state = &Events::KeyRelease;
  }

  KeyEvent keyboardEvent;
  keyboardEvent.mKey = aKey;
  keyboardEvent.mKeyboard = this;

  SendEvent(*state, &keyboardEvent);
}

bool Keyboard::IsShiftDown()
{
  return mShift;
}

bool Keyboard::IsControlDown()
{
  return mControl;
}

bool Keyboard::IsAltDown()
{
  return mAlt;
}
