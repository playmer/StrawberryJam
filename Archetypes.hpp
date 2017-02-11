#pragma once

#include "Composition.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

namespace Archetypes
{
  inline std::unique_ptr<Composition> Sprite(Space *aSpace, 
                                             const char *aName, 
                                             Texture *aTexture, 
                                             ShaderProgram *aShader)
  {
    auto compostiion = std::make_unique<Composition>(aSpace, aName);
    composition->
  }
}