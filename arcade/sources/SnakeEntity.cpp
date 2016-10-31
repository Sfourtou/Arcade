#include "SnakeEntity.hh"

SnakeEntity::SnakeEntity() //:
// ACharacter("Snake")
{

}

SnakeEntity::~SnakeEntity()
{
}

void SnakeEntity::setWay(InputButton::id_button dir)
{
  way = dir;
}

InputButton::id_button SnakeEntity::getWay()
{
  return way;
}

int SnakeEntity::getDirection(int x1, int y1, int x2, int y2)
{
  if (x1 - x2 > 0 && y1 - y2 == 0)
    return (BODY_RIGHT);
  else if (x1 - x2 < 0 && y1 - y2 == 0)
    return (BODY_LEFT);
  else if (y1 - y2 < 0 && x1 - x2 == 0)
    return (BODY_UP);
  else if (y1 - y2 > 0 && x1 - x2 == 0)
    return (BODY_DOWN);
  return (0);
}

const std::vector<SnakeBody *> &SnakeEntity::getBody() const
{
  return body;
}

void SnakeEntity::initSnakeBody(int x, int y, int accuracy)
{
  body.clear();
  SnakeBody *head = new SnakeBody();
  head->setPosX(x);
  head->setPosY(y);
  head->setState(HEAD_UP);
  SnakeBody *body1 = new SnakeBody();
  body1->setPosX(head->getPosX());
  body1->setPosY(head->getPosY() + accuracy);
  body1->setState(BODY_UP);
  SnakeBody *body2 = new SnakeBody();
  body2->setPosX(body1->getPosX());
  body2->setPosY(body1->getPosY() + accuracy);
  body2->setState(BODY_UP);
  SnakeBody *q = new SnakeBody();
  q->setPosX(body2->getPosX());
  q->setPosY(body2->getPosY() + accuracy);
  q->setState(Q_UP);
  body.push_back(head);
  body.push_back(body1);
  body.push_back(body2);
  body.push_back(q);
}

bool SnakeEntity::checkCollision(int x, int y) const
{
  for (std::vector<SnakeBody *>::const_iterator it = body.begin(); it != body.end(); ++it)
  {
    if (it != body.begin() && (*it)->getPosX() == x && (*it)->getPosY() == y)
      return (true);
  }
  return (false);
}

void SnakeEntity::growUp(int accuracy)
{
  int dir;
  SnakeBody *body1 = new SnakeBody();
  std::vector<SnakeBody *>::reverse_iterator next;
  std::vector<SnakeBody *>::reverse_iterator it;

  it = body.rbegin();
  next = std::next(it, 1);
  dir = getDirection((*next)->getPosX(), (*next)->getPosY(), (*it)->getPosX(), (*it)->getPosY());
  switch(dir)
  {
    case BODY_UP:
    body1->setPosX((*it)->getPosX());
    body1->setPosY((*it)->getPosY() - accuracy);
      break;
    case BODY_DOWN:
    body1->setPosX((*it)->getPosX());
    body1->setPosY((*it)->getPosY() + accuracy);
      break;
    case BODY_RIGHT:
    body1->setPosY((*it)->getPosY());
    body1->setPosX((*it)->getPosX() + accuracy);
      break;
    case BODY_LEFT:
    body1->setPosY((*it)->getPosY());
    body1->setPosX((*it)->getPosX() - accuracy);
      break;
  }
  body1->setState(dir);
  body.insert(body.end(), body1);
  //mouvement();
}

void SnakeEntity::mouvement()
{
  std::vector<SnakeBody *>::iterator it;
  (*body.begin())->setState(way - 1);
  for (it = body.begin(); it != body.end(); ++it)
  {
    std::vector<SnakeBody *>::iterator next;
    std::vector<SnakeBody *>::iterator prev;
    if (it != body.begin())
    {
      next = std::next(it, 1);
      prev = std::prev(it, 1);
      if (next != body.end())
        {
          int dir1 = getDirection((*prev)->getPosX(), (*prev)->getPosY(), (*it)->getPosX(), (*it)->getPosY());
          int dir2 = getDirection((*it)->getPosX(), (*it)->getPosY(), (*next)->getPosX(), (*next)->getPosY());
          if (dir1 == dir2)
          (*it)->setState(dir1);
          if ((dir1 == BODY_DOWN && dir2 == BODY_RIGHT) || (dir1 == BODY_LEFT && dir2 == BODY_UP))
            (*it)->setState(BODY_DOWN_LEFT);
          if ((dir1 == BODY_UP && dir2 == BODY_LEFT) || (dir1 == BODY_RIGHT && dir2 == BODY_DOWN))
            (*it)->setState(BODY_UP_RIGHT);
          if ((dir1 == BODY_LEFT && dir2 == BODY_DOWN) || (dir1 == BODY_UP && dir2 == BODY_RIGHT))
            (*it)->setState(BODY_UP_LEFT);
          if ((dir1 == BODY_RIGHT && dir2 == BODY_UP) || (dir1 == BODY_DOWN && dir2 == BODY_LEFT))
              (*it)->setState(BODY_DOWN_RIGHT);
        }
      else
        (*it)->setState(getDirection((*prev)->getPosX(), (*prev)->getPosY(), (*it)->getPosX(), (*it)->getPosY()) + 4);
    }
  }
}

void SnakeEntity::move(int x, int y)
{
  int tmpX;
  int tmpY;

  tmpX = 0;
  tmpY = 0;
  std::vector<SnakeBody *>::iterator it;
  for (it = body.begin(); it != body.end(); ++it)
  {
    int x1;
    int y1;
    x1 = (*it)->getPosX();
    y1 = (*it)->getPosY();
    if (it == body.begin())
    {
      (*it)->setPosX(x);
      (*it)->setPosY(y);
    }
    else
    {
      (*it)->setPosX(tmpX);
      (*it)->setPosY(tmpY);
    }
    tmpX = x1;
    tmpY = y1;
  }
  mouvement();
}

int SnakeEntity::getPosX() const
{
  return (*body.begin())->getPosX();
}

int SnakeEntity::getPosY() const
{
  return (*body.begin())->getPosY();
}
