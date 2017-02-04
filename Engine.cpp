#include "Engine.hpp"
#include "Space.hpp"

Engine::Engine()
  : mKeepRunning(true),
    mWindow("StrawberryJamGame", this),
    mKeyboard(this), 
    mMouse(this),
    mLastFrame(std::chrono::high_resolution_clock::now())
{
}

Engine::~Engine()
{
}

void Engine::MakeSpace(const char * aName)
{
  auto name = std::string(aName);
  mSpaces.emplace(name, std::make_unique<Space>(this, name));
}

void Engine::Update()
{
  using namespace std::chrono;
  auto deltaTime = high_resolution_clock::now() - mLastFrame;
  duration<double> timeSpan = duration_cast<duration<double>>(deltaTime);
  mLastFrame = std::chrono::high_resolution_clock::now();
  auto dt = timeSpan.count();

  mWindow.Update(dt);
  mKeyboard.Update();
  mMouse.Update();

  for (auto &space : mSpaces)
  {
    space.second->Update(dt);
  }
}
