#ifndef FRUIT_HH_
# define FRUIT_HH_

#include "ACharacter.hh"

class Fruit : public ACharacter
{
public:
  Fruit();
  ~Fruit();
private:
  int state;

public:
  void setState(int);
  int getState() const;
  virtual std::string getSprite() const;
};

#endif
