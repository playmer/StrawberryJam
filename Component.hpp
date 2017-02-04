#pragma once

#include "EventHandler.hpp"

class Component : public EventHandler
{
public:

  Component(Space *aSpace, Composition *aOwner)
    : mSpace(aSpace), mOwner(aOwner) {}
  virtual ~Component() {};

  Space* GetSpace() { return mSpace; }
  Composition* GetOwner() { return mOwner; }

private:
  Space *mSpace;
  Composition *mOwner;
};