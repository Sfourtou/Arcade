#include "Fruit.hh"

Fruit::Fruit() :
ACharacter("fruit"), state(0)
{

}

Fruit::~Fruit()

{
}

int Fruit::getState() const
{
  return state;
}

void Fruit::setState(int st)
{
  state = st;
}

std::string Fruit::getSprite() const
{
  return std::string("RedFruit");
}
