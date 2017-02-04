#include "Engine.hpp"

int main()
{
  Engine engine;
  engine.MakeSpace("MainSpace");

  while (engine.mKeepRunning)
  {
    engine.Update();
  }
}