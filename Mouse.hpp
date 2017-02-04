#pragma once

#include <glm/glm.hpp>

#include <string>

#include "Button.hpp"
#include "EventHandler.hpp"

#include "ForwardDeclarations.hpp"



// Mouse related event strings.
namespace Events
{
  extern const std::string MousePress;
  extern const std::string MouseRelease;
  extern const std::string MousePersist;
  extern const std::string MouseScroll;
  extern const std::string MouseMove;
}

enum class MouseButton : glm::u8
{
  Left = 1,
  Right = 2,
  Middle = 3,
  ScrollUp = 4,
  ScrollDown = 5
};

class Mouse : public EventHandler
{
public:
  Mouse(Engine *aEngine);
  ~Mouse();
  static void cursor_position_callback(GLFWwindow* aWindow, double aX, double aY);
  static void cursor_enter_callback(GLFWwindow* aWindow, int aEntered);
  static void mouse_button_callback(GLFWwindow* aWindow, int aButton, int aAction, int aMods);
  static void scroll_callback(GLFWwindow* aWindow, double aX, double aY);

  void Update();
  void UpdateButton(MouseButton aButton, int aAction);
  void UpdateMovement(glm::i32vec2 aMovement);


  // Lots of check functions I don't really need.
  inline ButtonState GetCurrentButtonState(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mCurrentState;
  }

  inline ButtonState GetPreviousButtonState(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mPreviousState;
  }

  inline bool IsButtonPressed(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mCurrentState == ButtonState::Pressed;
  }

  inline bool WasButtonPressed(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mPreviousState == ButtonState::Pressed;
  }

  inline bool IsButtonPersist(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mCurrentState == ButtonState::Persist;
  }

  inline bool WasButtonPersist(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mPreviousState == ButtonState::Persist;
  }

  inline bool IsButtonDown(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mCurrentState == ButtonState::Pressed ||
      mButtons[static_cast<char>(aButton)].mCurrentState == ButtonState::Persist;
  }

  inline bool WasButtonDown(MouseButton aButton)
  {
    return mButtons[static_cast<char>(aButton)].mPreviousState == ButtonState::Pressed ||
      mButtons[static_cast<char>(aButton)].mPreviousState == ButtonState::Persist;
  }

  Key mButtons[6];
  glm::i32vec2 mPosition;
  Engine *mEngine;
};

struct MouseEvent : public Event
{
  Mouse *mMouse;
  glm::i32vec2 mPosition;
  MouseButton mButton;
  bool mDown;
};



#pragma once
