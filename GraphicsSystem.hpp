#pragma once
#include "glm/glm.hpp"

#include "ForwardDeclarations.hpp"
#include "Sprite.hpp"

class GraphicsSystem
{
public:
  GraphicsSystem(Space *aSpace, glm::vec4 aClearColor);
  void Update(double aDt);

  Space *mSpace;
  Mesh mMesh;
  glm::vec4 mClearColor;
};