#pragma once

#include <glm/glm.hpp>

enum class ButtonState : glm::u8
{
  Pressed = 0,
  Persist = 1,
  Released = 2,
  Up = 3,
};

struct Key
{
  // We get a warning about this on g++ due to a ~5 year old bug.
  // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51242
  ButtonState mPreviousState : 2;
  ButtonState mCurrentState : 2;
};