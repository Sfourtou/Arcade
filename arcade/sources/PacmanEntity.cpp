/*
** PacmanEntity for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 20:31:05 2016 fourto_s
** Last update Sat Apr 02 23:50:13 2016 Sebastien Fourtou
*/

#include "PacmanEntity.hh"
#include "Ghost.hh"
#include "PacMan.hh"

PacmanEntity::PacmanEntity() :
  ACharacter("pacman"), state(false), lifes(2), way(InputButton::UNDEF), speed(SPEED)
{
  button = InputButton::UNDEF;
}

PacmanEntity::~PacmanEntity()
{
}

void PacmanEntity::setState(bool new_state)
{
  state = new_state;
}

bool PacmanEntity::getState() const
{
  return state;
}

size_t PacmanEntity::getLifes() const
{
  return lifes;
}

void PacmanEntity::setLifes(size_t new_lifes)
{
  lifes = new_lifes;
}

std::string PacmanEntity::getSprite() const
{
  std::string * dir = new std::string[20];
  std::string state_str;

  dir[InputButton::UNDEF] = "Left";
  dir[InputButton::LEFT] = "Left";
  dir[InputButton::RIGHT] = "Right";
  dir[InputButton::UP] = "Up";
  dir[InputButton::DOWN] = "Down";
  if (state)
    state_str = "True";
  else
    state_str = "False";
  return (std::string("pac") + dir[way] + state_str);
}

InputButton::id_button PacmanEntity::getWay() const
{
  return way;
}

void PacmanEntity::setWay(InputButton::id_button new_way)
{
  way = new_way;
}



bool PacmanEntity::touchedGhost(std::vector<Ghost *> & ghosts, int tileSize)
{
  int xGhost;
  int yGhost;

  for (std::vector<Ghost *>::iterator it = ghosts.begin() ; it != ghosts.end() ; ++it)
  {
    xGhost = (*it)->getPosX() + 12;
    yGhost = (*it)->getPosY() + 12;

    if ((posX < xGhost && xGhost < posX + tileSize && posY < yGhost && yGhost < posY + tileSize) && (*it)->isEaten() == false)
    {
      if ((*it)->isFrightened())
      {
        (*it)->setBeingEat(true);
        (*it)->setHasBeenEat(true);
      }
      return true;
    }
  }
  return false;
}

void PacmanEntity::setSpeed(int new_speed)
{
  speed = new_speed;
}
