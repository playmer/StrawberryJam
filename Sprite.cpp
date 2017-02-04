#include "GL/glew.h"

#include "GraphicsSystem.hpp"
#include "Space.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"


DefineType(Sprite);

Sprite::Sprite(Space *aSpace,
               Composition *aOwner,
               ShaderProgram *aProgram,
               Mesh *aMesh,
               Texture *aTexture)
  : Component(aSpace, aOwner),
    mProgram(aProgram), 
    mMesh(aMesh), 
    mTexture(aTexture)
{
  mMesh = &aSpace->GetGraphicsSystem()->mMesh;
} 

void Sprite::Draw()
{
  mProgram->Bind();
  mTexture->Bind(0, mProgram->mHandle.get());
  mMesh->Bind();

  glDrawArrays(GL_TRIANGLES, 0, 3);

  mMesh->Unbind();
  mTexture->Unbind();
  mProgram->Unbind();
}

Mesh::Mesh()
{
  // Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
  };
  GLuint indices[] = 
  {  // Note that we start from 0!
    0, 1, 3, // First Triangle
    1, 2, 3  // Second Triangle
  };

  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);

  glBindVertexArray(mVAO);

  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO
}

Mesh::~Mesh()
{
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &mVAO);
  glDeleteBuffers(1, &mVBO);
  glDeleteBuffers(1, &mEBO);
}

void Mesh::Bind()
{
  glBindVertexArray(mVAO);
}

void Mesh::Unbind()
{
  glBindVertexArray(0);
}
