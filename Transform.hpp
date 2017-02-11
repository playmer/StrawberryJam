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

  glm::vec3 GetTranslation() { return mTranslation; };
  glm::vec3 GetScale() { return mScale; };
  glm::vec3 GetRotation() { return mRotation; };
  void SetTranslation(glm::vec3 &aTranslation) { mTranslation = aTranslation; };
  void SetScale(glm::vec3 &aScale) { mScale = aScale; };
  void SetRotation(glm::vec3 &aRotation) { mRotation = aRotation; };

private:
  glm::vec3 mTranslation;
  glm::vec3 mScale;
  glm::vec3 mRotation;
};

DeclareTypeHelper(Transform);