#include "GL/glew.h"
#include "GraphicsSystem.hpp"


GraphicsSystem::GraphicsSystem(Space *aSpace, glm::vec4 aClearColor)
  : mSpace(aSpace), mClearColor(aClearColor)
{

}

void GraphicsSystem::Update(double aDt)
{
  glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
