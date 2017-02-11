#pragma once
#include <memory>
#include <unordered_map>

#include "Component.hpp"
#include "EventHandler.hpp"
#include "Types.hpp"


class Composition : public EventHandler
{
public:
  Composition(Space *aSpace, const char *aName = "");

  template<typename ComponentType, typename... Arguments>
  ComponentType* AddComponent(Arguments &&...aArguments)
  {
    auto it = mComponents.emplace(GetType<ComponentType>(),
      std::make_unique<ComponentType>(std::forward<Arguments &&>(aStoredTypeArguments)...));

    return static_cast<ComponentType*>(it.second.get());
  }

  template<typename ComponentType>
  ComponentType* GetComponent()
  {
    auto it mComponents.find(GetType<ComponentType>());

    return (it != mComponents.end()) ? static_cast<ComponentType*>(it.second.get()) : nullptr;
  }

  Space* GetSpace() { return mSpace; }

  void ChangeName(const char *aName) { mName = aName; }


private:
  Space *mSpace;
  std::string mName;
  ComponentMap mComponents;
};