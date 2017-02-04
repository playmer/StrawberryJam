#pragma once
#include "Button.hpp"
#include "EventHandler.hpp"

namespace Events
{
  extern const std::string KeyPress;
  extern const std::string KeyRelease;
  extern const std::string KeyPersist;
}

class Keyboard : public EventHandler
{
public:
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  Keyboard(Engine *mEngine);
  ~Keyboard();
  void Update();
  void UpdateKey(char aKey, int aAction);

  // Lots of check functions I don't really need.
  inline ButtonState GetCurrentKeyState(int aKey)
  {
    return mKeys[aKey].mCurrentState;
  }

  inline ButtonState GetPreviousKeyState(int aKey)
  {
    return mKeys[aKey].mPreviousState;
  }

  inline bool IsKeyPressed(int aKey)
  {
    return mKeys[aKey].mCurrentState == ButtonState::Pressed;
  }

  inline bool WasKeyPressed(int aKey)
  {
    return mKeys[aKey].mPreviousState == ButtonState::Pressed;
  }

  inline bool IsKeyPersist(int aKey)
  {
    return mKeys[aKey].mCurrentState == ButtonState::Persist;
  }

  inline bool WasKeyPersist(int aKey)
  {
    return mKeys[aKey].mPreviousState == ButtonState::Persist;
  }

  inline bool IsKeyDown(int aKey)
  {
    return mKeys[aKey].mCurrentState == ButtonState::Pressed ||
      mKeys[aKey].mCurrentState == ButtonState::Persist;
  }

  inline bool WasKeyDown(int aKey)
  {
    return mKeys[aKey].mPreviousState == ButtonState::Pressed ||
           mKeys[aKey].mPreviousState == ButtonState::Persist;
  }

  // Modifier check functions. These check the current state 
  // according to the OS. Not our cached results.
  bool IsShiftDown();
  bool IsControlDown();
  bool IsAltDown();

  Engine *mEngine;

  //I only really need 348 but whatever, GLFW makes me sad.
  Key mKeys[400];

  bool mShift;
  bool mControl;
  bool mAlt;
};

struct KeyEvent : public Event
{
  Keyboard *mKeyboard;
  char mKey;
};
