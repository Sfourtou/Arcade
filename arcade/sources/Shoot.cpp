#include "Shoot.hh"

Shoot::Shoot(int y, int x)
   : ACharacter("shoot")
{
   setStartY(y);
   setStartX(x);
   setPosY(y);
   setPosX(x);
}

Shoot::~Shoot()
{
}

std::string
Shoot::getSprite() const
{
   return ("Shoot");
}
