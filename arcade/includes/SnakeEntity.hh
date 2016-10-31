#ifndef SNAKEENTITY
#define SNAKEENTITY

#include <vector>
#include "SnakeBody.hh"
#include "Map.hh"

class SnakeEntity
{
public:
  SnakeEntity();
  ~SnakeEntity();

public:
  void setWay(InputButton::id_button);
  void initSnakeBody(int,int,int);
  void move(int x, int y);
  bool checkCollision(int x, int y) const;
  void growUp(int);
  const std::vector<SnakeBody *> &getBody() const;
  int getPosX() const;
  int getPosY() const;
  InputButton::id_button getWay();

private:
  int getDirection(int, int, int, int);
  void mouvement();

private:
  InputButton::id_button way;
  std::vector<SnakeBody *> body;
};

#endif
