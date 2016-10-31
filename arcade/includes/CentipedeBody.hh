#ifndef CENTIPEDEBODY_HH_
# define CENTIPEDEBODY_HH_

#include "ACharacter.hh"

class CentipedeBody : public ACharacter
{
public:
   CentipedeBody(std::string const &s = "CentiBody");
   ~CentipedeBody();
   void setSprite(const std::string &);
   std::string getSprite() const;
private:
   std::string sprite;
};

#endif
