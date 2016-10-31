#ifndef SHIP_HH_
# define SHIP_HH_

# include "Shoot.hh"
# include "ACharacter.hh"

class Ship : public ACharacter
{
public:
   Ship();
   ~Ship();
   std::string getSprite() const;
   Shoot *createShoot(int accuracy) const;
};

#endif
