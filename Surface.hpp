#pragma once

#include "ForwardDeclarations.hpp"

class Surface
{
public:
  Surface(const char *aTitle, Engine *mEngine);
  ~Surface();

  void Update(double aDt);

  GLFWwindow *mWindow;
  Engine *mEngine;
  int mWidth;
  int mHeight;
};