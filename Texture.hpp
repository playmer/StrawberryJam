#pragma once
#include <string>

extern const std::string gDefaultNormal;

class Texture
{
public:
  Texture(const char *filename);

  void Bind(const int unit, const int programId);
  void Unbind();

private:
  unsigned int mTextureId;
  bool mLoaded = true;
};