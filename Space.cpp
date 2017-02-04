#include "Composition.hpp"
#include "Space.hpp"

Space::Space(Engine * aEngine, std::string &aName)
  : mEngine(aEngine), 
    mName(aName), 
    mGraphicsSystem(this, { 0.2f, 0.3f, 0.3f, 1.0f })
{

}

Space::~Space()
{
}

void Space::Update(double aDt)
{
  mGraphicsSystem.Update(aDt);
}
