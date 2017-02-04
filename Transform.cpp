#include "Transform.hpp"

DefineType(Transform)


Transform::Transform(Space *aSpace,
                     Composition *aOwner,
                     glm::vec3 aTranslation,
                     glm::vec3 aScale,
                     glm::vec3 aRotation)
  : Component(aSpace, aOwner),
    mTranslation(aTranslation),
    mScale(aScale),
    mRotation(aRotation)
{
} 