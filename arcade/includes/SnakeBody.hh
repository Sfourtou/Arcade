#ifndef SNAKEBODY_HH_
# define SNAKEBODY_HH_

#include <map>
#include "ACharacter.hh"

class SnakeBody : public ACharacter
{
public:
  SnakeBody();
  ~SnakeBody();
private:
  int state;

public:
  void setState(int);
  int getState() const;
  virtual std::string getSprite() const;
};

enum BodyState
{
  HEAD_UP,
  HEAD_DOWN,
  HEAD_RIGHT,
  HEAD_LEFT,
  BODY_DOWN_RIGHT,
  BODY_DOWN_LEFT,
  BODY_UP_RIGHT,
  BODY_UP_LEFT,
  BODY_UP,
  BODY_DOWN,
  BODY_RIGHT,
  BODY_LEFT,
  Q_UP,
  Q_DOWN,
  Q_RIGHT,
  Q_LEFT,
};

#endif
