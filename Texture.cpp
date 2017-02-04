#include <array>
#include <cmath>
#include <fstream>
#include <stdlib.h>

#include "GL/glew.h"
#include "stb/stb_image.h"

#include "Texture.hpp"


extern const std::string gDefaultNormal = "Default";

struct STBColor
{
  unsigned char r, g, b, a;
};

static std::array<STBColor, 4 * 32 * 32> gColor;

Texture::Texture(const char *aPath) : mTextureId(0)
{
  std::string path = aPath;
  if (path.size() == 0)
  {
    mLoaded = false;
    return;
  }

  unsigned char* image = nullptr;
  int width, height, n;

  if (path == gDefaultNormal)
  {
    static bool notRun = true;
    STBColor colorToSet = { 128,128,255, 255 };

    if (notRun)
    {
      for (auto &color : gColor)
      {
        color = colorToSet;
      }

      notRun = false;
    }

    width = 32;
    height = 32;

    image = &(gColor.data()->r);
  }
  else
  {
    std::string texturePath = std::string("./textures/") + path;
    stbi_set_flip_vertically_on_load(true);

    image = stbi_load(texturePath.c_str(), &width, &height, &n, 4);
    if (!image) {
      printf("\nRead error on file %s:\n  %s\n\n", texturePath.c_str(), stbi_failure_reason());
      exit(-1);
    }
  }

  glGenTextures(1, &mTextureId);
  glBindTexture(GL_TEXTURE_2D, mTextureId);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 100);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)GL_LINEAR_MIPMAP_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);


  if (path != gDefaultNormal)
  {
    stbi_image_free(image);
  }
}

void Texture::Bind(const int unit, const int programId)
{
  if (false == mLoaded)
  {
    return;
  }

  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, mTextureId);
  int loc = glGetUniformLocation(programId, "texSampler");
  glUniform1i(loc, unit);
}

void Texture::Unbind()
{
  if (false == mLoaded)
  {
    return;
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}