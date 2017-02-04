#pragma once
#include <memory>
#include <unordered_map>

#include "Component.hpp"
#include "EventHandler.hpp"
#include "Types.hpp"


class Composition : public EventHandler
{
public:
  Composition();
private:
  Space *mSpace;
  ComponentMap mComponents;
};