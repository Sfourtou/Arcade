#include "SnakeBody.hh"

SnakeBody::SnakeBody() :
ACharacter("Snake"), state(0)
{

}

SnakeBody::~SnakeBody()

{
}

int SnakeBody::getState() const
{
  return state;
}

void SnakeBody::setState(int st)
{
  state = st;
}

std::string SnakeBody::getSprite() const
{
  std::map<int, std::string> sprites;

  sprites[HEAD_UP] = "GreenSnakeHeadUp";

  sprites[HEAD_DOWN] = "GreenSnakeHeadDown";
  sprites[HEAD_RIGHT] = "GreenSnakeHeadRight";
  sprites[HEAD_LEFT] = "GreenSnakeHeadLeft";

  sprites[BODY_DOWN_RIGHT] = "GreenSnakeBodyDownToRight";
  sprites[BODY_DOWN_LEFT] = "GreenSnakeBodyDownToLeft";
  sprites[BODY_UP_RIGHT] = "GreenSnakeBodyUpToRight";
  sprites[BODY_UP_LEFT] = "GreenSnakeBodyUpToLeft";

  sprites[BODY_UP] = "GreenSnakeBodyY";
  sprites[BODY_DOWN] = "GreenSnakeBodyY";
  sprites[BODY_RIGHT] = "GreenSnakeBodyX";
  sprites[BODY_LEFT] = "GreenSnakeBodyX";
  sprites[Q_UP] = "GreenSnakeQUp";
  sprites[Q_RIGHT] = "GreenSnakeQRight";
  sprites[Q_LEFT] = "GreenSnakeQLeft";
  sprites[Q_DOWN] = "GreenSnakeQDown";
  return sprites[state];
}
