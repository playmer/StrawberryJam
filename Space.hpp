#pragma once

#include "EventHandler.hpp"
#include "GraphicsSystem.hpp"
#include "Types.hpp"

class Space : public EventHandler
{
public:
  Space(Engine *aEngine, std::string &aName);
  ~Space();

  void Update(double aDt);

  GraphicsSystem* GetGraphicsSystem() { return &mGraphicsSystem; }

  Composition* CreateObject();

private:
  Engine *mEngine;
  std::string mName;

  CompositionMap mCompositions;
  GraphicsSystem mGraphicsSystem;
};