#pragma once

#include <chrono>

#include "EventHandler.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Surface.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


class Engine : public EventHandler
{
public:
  Engine();
  ~Engine();

  void MakeSpace(const char *aName);

  void Update();


  bool mKeepRunning;

  Surface mWindow;
  Keyboard mKeyboard;
  Mouse mMouse; 
  std::chrono::time_point<std::chrono::high_resolution_clock> mLastFrame;
  SpaceMap mSpaces;

  std::unordered_map<std::string, ShaderProgram> mShaderPrograms;
  std::unordered_map<std::string, Texture> mTextures;
};