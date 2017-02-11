#pragma once
#include "glm/glm.hpp"

#include "ForwardDeclarations.hpp"
#include "Sprite.hpp"

DeclareShader(Sprite)
DeclareTexture(Happy)
DeclareTexture(Skeleman)

class GraphicsSystem
{
public:
  GraphicsSystem(Space *aSpace, glm::vec4 aClearColor);
  void Update(double aDt);



  Space *mSpace;
  Mesh mMesh;
  glm::vec4 mClearColor;
  std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
  std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> mShaders;
};