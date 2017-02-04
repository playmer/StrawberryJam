#pragma once
#include "Component.hpp"
#include "ForwardDeclarations.hpp"

class Transform : public Component
{
public:
  DeclareType(Transform);
  Transform(Space *aSpace,
            Composition *aOwner,
            glm::vec3 mTranslation,
            glm::vec3 mScale,
            glm::vec3 mRotation);

private:
  glm::vec3 mTranslation;
  glm::vec3 mScale;
  glm::vec3 mRotation;
};

DeclareTypeHelper(Transform);