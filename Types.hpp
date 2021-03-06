//////////////////////////////////////////////
// Author: Joshua T. Fisher
//////////////////////////////////////////////
#pragma once

#ifndef Types_hpp
#define Types_hpp

#include <stdint.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ForwardDeclarations.hpp"

using byte = std::uint8_t;

using i8 =  std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

// The fact that I actually have to do this makes me sick.
using namespace std::string_literals;

class Type
{
public:
  Type(const char *aName)
    : mName(aName)
  {
    mHash = std::hash<std::string>{}(mName);
  }

  const std::string& Name() { return mName; }

  // Don't really need to do this, but w/e.
  bool operator==(const Type &aRight)
  {
    if ((mHash == aRight.mHash) && (mName == aRight.mName))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

private:
  std::string mName;
  size_t mHash;
};

template<typename T>
Type* GetType()
{
  return nullptr;
}


// Used to declare a static type within a class
// Requires DefineType be used at some point in a
// translation unit.
#define DeclareType(Name) \
static Type sType;        \
Type* GetType() override; \

#define DefineType(Name)      \
Type Name::sType = { #Name }; \
Type* Name::GetType() { return &sType; }; 

// "Optional" Helper so any type pointer can
// be obtained statically.
#define DeclareTypeHelper(Name) \
namespace Types                 \
{                               \
  extern Type *Name;            \
}                               \
                                \
template <>                     \
inline Type* GetType<Name>()    \
{                               \
  return &Name::sType;          \
}



#define DeclareShader(aName)      \
namespace Shaders                 \
{                                 \
  extern const std::string aName; \
}

#define DefineShader(aName)           \
namespace Shaders                     \
{                                     \
  const std::string aName { #aName }; \
}

#define DeclareTexture(aName)     \
namespace Textures                \
{                                 \
  extern const std::string aName; \
}

#define DefineTexture(aName)          \
namespace Textures                    \
{                                     \
  const std::string aName { #aName }; \
}


class Base
{
  virtual Type *GetType() = 0;
};



using ComponentMap = std::unordered_map<Type*, std::unique_ptr<Component>>;
using CompositionMap = std::unordered_map<std::string, std::unique_ptr<Composition>>;
using SpaceMap = std::unordered_map<std::string, std::unique_ptr<Space>>;


// Helper to capture the destructor of a type.
template <typename T>
void GenericDestruct(byte *aMemory)
{
  (reinterpret_cast<T*>(aMemory))->~T();
}

// Helper to call the constructor of a type.
template <typename T>
void GenericDefaultConstruct(byte *aMemory)
{
  new (aMemory) T();
}

// Helper to call the constructor of a type.
inline void GenericDoNothing(byte *aMemory)
{
}

inline void runtime_assert(bool aValue, const char *aMessage = "")
{
  if (false == aValue)
  {
    printf("ASSERT: %s\n", aMessage);

    // Purposely ruining this programs life.
    int *base = nullptr;
    *base = 1;
  }
}


inline glm::mat4 Rotate(glm::mat4 &aMatrix, glm::vec3 aRotation)
{
  float xCos = cos(aRotation.x);
  float xSin = sin(aRotation.x);
  float yCos = cos(aRotation.y);
  float ySin = sin(aRotation.y);
  float zCos = cos(aRotation.z);
  float zSin = sin(aRotation.z);

  float ySin_zCos = ySin * zCos;

  glm::mat4 rotation(glm::uninitialize);
  rotation[0][0] = yCos * zCos;
  rotation[0][1] = -yCos * zSin;
  rotation[0][2] = ySin;

  rotation[1][0] = xCos * zSin + xSin * ySin_zCos;
  rotation[1][1] = xCos * zCos - xSin * ySin * zSin;
  rotation[1][2] = -xSin * yCos;

  rotation[2][0] = xSin * zSin - xCos * ySin_zCos;
  rotation[2][1] = xCos * ySin * zSin + xSin * zCos;
  rotation[2][2] = xCos * yCos;


  glm::mat4 result(glm::uninitialize);
  result[0] = aMatrix[0] * rotation[0][0] + 
              aMatrix[1] * rotation[0][1] + 
              aMatrix[2] * rotation[0][2];

  result[1] = aMatrix[0] * rotation[1][0] + 
              aMatrix[1] * rotation[1][1] + 
              aMatrix[2] * rotation[1][2];
  result[2] = aMatrix[0] * rotation[2][0] + 
              aMatrix[1] * rotation[2][1] + 
              aMatrix[2] * rotation[2][2];
  result[3] = aMatrix[3];

  return result;
}


enum class StringComparison
{
  String1Null,     // (We check this first)
  LesserInString1, // The first character that does not match has a lower value in ptr1 than in ptr2
  Equal,
  GreaterInString1,// The first character that does not match has a greater value in ptr1 than in ptr2
  String2Null,     // (We check this Second)
};

inline StringComparison StringCompare(const char *aLeft, const char *aRight)
{
  if (nullptr == aLeft)
  {
    return StringComparison::String1Null;
  }

  if (nullptr == aRight)
  {
    return StringComparison::String2Null;
  }

  auto comparison = std::strcmp(aLeft, aRight);

  if (0 == comparison)
  {
    return StringComparison::Equal;
  }
  else if (comparison < 0)
  {
    return StringComparison::LesserInString1;
  }
  else // if (comparison < 0) This is by definition of the domain, no need to check
  {
    return StringComparison::GreaterInString1;
  }
}

#endif