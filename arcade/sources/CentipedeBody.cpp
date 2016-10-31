#include "CentipedeBody.hh"

CentipedeBody::CentipedeBody(std::string const &n)
   : ACharacter("CentipedeBody"), sprite(n)
{
}

CentipedeBody::~CentipedeBody()
{
}

void
CentipedeBody::setSprite(std::string const &s)
{
   sprite = s;
}

std::string
CentipedeBody::getSprite() const
{
   return (sprite);
}
