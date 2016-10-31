#ifndef SHOOT_HH_
# define SHOOT_HH_

# include "ACharacter.hh"

class Shoot : public ACharacter
{
public:
   Shoot(int y, int x);
   ~Shoot();
   std::string getSprite() const;
};

#endif
