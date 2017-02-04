#pragma once
#include <stddef.h>
#include <iostream>
#include <vector>


#include "UniqueHandle.hpp"

using OpenGLHandle = UniqueHandle<unsigned int>;

bool PrintShaderError(unsigned int aShader, unsigned int aType);

void DeleteShader(unsigned int aShader);;



inline OpenGLHandle CreateShader(const char *aSource, unsigned int aType);



inline void DeleteShaderProgram(unsigned int aShaderProgram);;

class ShaderProgram
{
public:
  void Bind();

  void Unbind()
  {
    mCurrentlyUsed = false;
  }

  OpenGLHandle mHandle;
  bool mCurrentlyUsed;
};


inline OpenGLHandle CreateShaderProgram(std::vector<OpenGLHandle> &aShaders);
