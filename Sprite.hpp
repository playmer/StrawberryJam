#pragma once

#include "Component.hpp"
#include "ForwardDeclarations.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class Shader;

struct Mesh
{
  Mesh();
  ~Mesh();
  void Bind();
  void Unbind();

  unsigned int mVBO;
  unsigned int mVAO;
  unsigned int mEBO;
};

class Sprite : public Component
{
public:
  DeclareType(Sprite);
  Sprite(Space *aSpace, 
         Composition *aOwner, 
         ShaderProgram *aProgram, 
         Mesh *aMesh, 
         Texture *aTexture);
  

  ShaderProgram *mProgram;
  Mesh *mMesh;
  Texture *mTexture;

  void Draw();
};

DeclareTypeHelper(Sprite);
