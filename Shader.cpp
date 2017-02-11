#include <fstream>

#include "GL/glew.h"

#include "Shader.hpp"

bool PrintShaderError(unsigned int aShader, unsigned int aType)
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

static std::string ReadFileToString(const char *aFile)
{
  std::string output;;
  std::ifstream stream(aFile);

  if (!stream.fail())
  {
    stream.seekg(0, std::ios::end);
    output.reserve(static_cast<unsigned int>(stream.tellg()));
    stream.seekg(0, std::ios::beg);

    output.assign((std::istreambuf_iterator<char>(stream)),
                  std::istreambuf_iterator<char>());
    return output;
  }

  return output;
}

ShaderProgram::ShaderProgram(const char *aVertex, const char *aFragment)
{
  auto vertexSource = ReadFileToString(aVertex);
  auto fragmentSource = ReadFileToString(aFragment);

  auto vertex = CreateShader(vertexSource.c_str(), GL_VERTEX_SHADER);
  auto fragment = CreateShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertex.get());
  glAttachShader(shaderProgram, fragment.get());

  glLinkProgram(shaderProgram);

  glDetachShader(shaderProgram, vertex.get());
  glDetachShader(shaderProgram, fragment.get());

  GLint success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (success)
  {
    mHandle = OpenGLHandle(shaderProgram, DeleteShaderProgram);
  }
  else
  {
    GLchar infoLog[512];

    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
}

void ShaderProgram::Bind()
{
  if (mCurrentlyUsed)
    return;

  glUseProgram(mHandle.get());
  mCurrentlyUsed = true;
}
