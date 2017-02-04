#include "GL/glew.h"

#include "Shader.hpp"

bool PrintShaderError(GLuint aShader, unsigned int aType)
{
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(aShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(aShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::";

    switch (aType)
    {
      case GL_VERTEX_SHADER:
      {
        std::cout << "VERTEX";
        break;
      }
      case GL_GEOMETRY_SHADER:
      {
        std::cout << "GEOMETRY";
        break;
      }
      case GL_COMPUTE_SHADER:
      {
        std::cout << "COMPUTE";
        break;
      }
      case GL_FRAGMENT_SHADER:
      {
        std::cout << "FRAGMENT";
        break;
      }
      case GL_TESS_CONTROL_SHADER:
      {
        std::cout << "FRAGMENT";
        break;
      }
      case GL_TESS_EVALUATION_SHADER:
      {
        std::cout << "FRAGMENT";
        break;
      }
    }

    std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return success == 0;
}

void DeleteShader(unsigned int aShader)
{
  if (aShader != 0)
  {
    std::cout << "Deleting shader: " << aShader << std::endl;
    glDeleteShader(aShader);
  }
}

OpenGLHandle CreateShader(const char * aSource, unsigned int aType)
{
  unsigned int shader;
  shader = glCreateShader(aType);

  glShaderSource(shader, 1, &aSource, NULL);
  glCompileShader(shader);


  if (!PrintShaderError(shader, aType))
  {
    OpenGLHandle shaderPtr(shader, DeleteShader);

    return std::move(shaderPtr);
  }
  else
  {
    unsigned int nullShader;
    OpenGLHandle shaderPtr(nullShader, DeleteShader);
    return std::move(shaderPtr);
  }
}

void DeleteShaderProgram(unsigned int aShaderProgram)
{
  if (aShaderProgram != 0)
  {
    std::cout << "Deleting shader: " << aShaderProgram << std::endl;
    glDeleteProgram(aShaderProgram);
  }
}

OpenGLHandle CreateShaderProgram(std::vector<OpenGLHandle>& aShaders)
{
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  for (auto &shader : aShaders)
  {
    glAttachShader(shaderProgram, shader.get());
  }

  glLinkProgram(shaderProgram);

  for (auto &shader : aShaders)
  {
    glDetachShader(shaderProgram, shader.get());
  }

  GLint success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success)
  {
    GLchar infoLog[512];

    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  if (success)
  {
    OpenGLHandle shaderPtr(shaderProgram, DeleteShaderProgram);

    return std::move(shaderPtr);
  }
  else
  {
    unsigned int nullShader;
    OpenGLHandle shaderPtr(nullShader, DeleteShaderProgram);
    return std::move(shaderPtr);
  }
}

void ShaderProgram::Bind()
{
  if (mCurrentlyUsed)
    return;

  glUseProgram(mHandle.get());
  mCurrentlyUsed = true;
}
