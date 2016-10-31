#ifndef MUSHROOM_HH_
# define MUSHROOM_HH_

#include "ACharacter.hh"

class Mushroom : public ACharacter
{
public:
   Mushroom();
   ~Mushroom();
   std::string getSprite() const;
   int decrLife();
private:
   // between 4 and 0
   int lifes;
};

#endif
