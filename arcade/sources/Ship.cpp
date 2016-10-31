#include "Ship.hh"

Ship::Ship()
   : ACharacter("Ship")
{

}

Ship::~Ship()
{

}

std::string
Ship::getSprite() const
{
   return ("BlueShip");
}

Shoot *
Ship::createShoot(int accuracy) const
{
   return (new Shoot(getPosY() - accuracy, getPosX()));
}
