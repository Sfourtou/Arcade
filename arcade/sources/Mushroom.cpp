#include "Mushroom.hh"

Mushroom::Mushroom()
   : ACharacter("Ship"), lifes(4)
{
}

Mushroom::~Mushroom()
{
}

std::string
Mushroom::getSprite() const
{
   std::string tab[4] = {
      "QMushroom",
      "HMushroom",
      "TMushroom",
      "FMushroom"
   };
   return (tab[(lifes - 1)]);
}

int
Mushroom::decrLife()
{
   if (lifes - 1 >= 0)
      --lifes;
   return lifes;
}
