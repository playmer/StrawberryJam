#include "GL/glew.h"
#include "GraphicsSystem.hpp"


DefineShader(Sprite)
DefineTexture(Happy)
DefineTexture(Skeleman)


GraphicsSystem::GraphicsSystem(Space *aSpace, glm::vec4 aClearColor)
  : mSpace(aSpace), mClearColor(aClearColor)
{
  auto sprite = std::make_unique<ShaderProgram>("./Shaders/SpriteVertex.glsl", 
                                                "./Shaders/SpriteFragment.glsl");
  mShaders.emplace(Shaders::Sprite, std::move(sprite));

  auto happy = std::make_unique<Texture>("Happy.png");
  mTextures.emplace(Textures::Happy, std::move(happy));

  auto skele = std::make_unique<Texture>("Skeleman.png");
  mTextures.emplace(Textures::Skeleman, std::move(skele));
}

void GraphicsSystem::Update(double aDt)
{
  glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
