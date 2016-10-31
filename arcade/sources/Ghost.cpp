/*
** Ghost.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Fri Mar 18 17:57:45 2016 fourto_s
** Last update Sat Apr 02 23:46:27 2016 Sebastien Fourtou
*/

#include <math.h>
#include "Ghost.hh"
#include "Utils.hh"

#define ABS(x) x < 0 ? x * (-1) : x

Ghost::Ghost(const std::string & name) :
  ACharacter(name), state(false), frightened(false), my_button(InputButton::UNDEF), search(false), changeDir(false), inBox(true), hasBeenEat(false), state_frightened(false), eat(false), speed(SPEED)
{
}

Ghost::~Ghost()
{
}

bool Ghost::isWalkable(int nb_case)
{
  int walkable[14] = {START_CASE, NORMAL_PAC_GUM, BIG_PAC_GUM, BIG_PAC_GUM_LIGHT, TP_LEFT, TP_RIGHT, START_RED, START_ORANGE, START_BLUE, 0, 999, 0, 90, STOP};
  if (inBox == true || hasBeenEat == true)
    walkable[11] = 50;
  for (int i = 0 ; walkable[i] != STOP ; ++i)
  {
    if (nb_case == walkable[i])
      return true;
  }
  return false;
}

bool Ghost::gere_collision_x(Map & map, int col, int tileSize)
{
  int * mapi = map.getMap();

  for (int y = 0; y != tileSize; ++y)
  {
    int nb = mapi[(posX + col) / tileSize + (posY + y) / tileSize * map.getWidth()];
    if (!isWalkable(nb))
      return false;
  }
  return true;
}

bool Ghost::gere_collision_y(Map & map, int col, int tileSize)
{
  int * mapi = map.getMap();

  for (int x = 0; x != tileSize; ++x)
  {
    int nb = mapi[(posX + x) / tileSize + (posY + col) / tileSize * map.getWidth()];
    if (!isWalkable(nb))
      return false;
  }
  return true;
}

void Ghost::move(Map & map, InputButton::id_button id, int tileSize)
{
  int * mapi = map.getMap();

  if (!frightened)
  {
    posX = (posX) % 2 == 1 ? ((my_button == InputButton::LEFT) ? posX - 1 : posX + 1) : posX;
    posY = (posY) % 2 == 1 ? ((my_button == InputButton::UP) ? posY - 1 : posY + 1) : posY;
  }
  bool left = gere_collision_x(map, -speed / 2, tileSize);
  bool right = gere_collision_x(map, tileSize, tileSize);
  bool up = gere_collision_y(map, -speed / 2, tileSize);
  bool down = gere_collision_y(map, tileSize, tileSize);

  if (id == InputButton::LEFT && left)
  {
    (frightened || map.getMap()[(getPosX()) / tileSize + getPosY() / tileSize * map.getWidth()] == 90) ? posX -= speed / 2: posX -= speed;
    button = InputButton::LEFT;
    my_button = InputButton::LEFT;
  }
  else if (id == InputButton::RIGHT && right)
  {
    (frightened || map.getMap()[(getPosX() + tileSize) / tileSize + getPosY() / tileSize * map.getWidth()] == 90) ? posX += speed / 2 : posX += speed;

    button = InputButton::RIGHT;
    my_button = InputButton::RIGHT;
  }
  else if (id == InputButton::UP && up)
  {
    (!frightened) ? posY -= speed : posY -= speed / 2;
    button = InputButton::UP;
    my_button = InputButton::UP;
  }
  else if (id == InputButton::DOWN && down)
  {
    (!frightened) ? posY += speed : posY += speed / 2;
    button = InputButton::DOWN;
    my_button = InputButton::DOWN;
  }
  else
  {
    if (my_button == InputButton::LEFT && left)
      (!frightened) ? posX -= speed : posX -= speed / 2;
    else if (my_button == InputButton::RIGHT && right)
      (!frightened) ? posX += speed : posX += speed / 2;
    else if (my_button == InputButton::UP && up)
      (!frightened) ? posY -= speed : posY -= speed / 2;
    else if (my_button == InputButton::DOWN && down)
      (!frightened) ? posY += speed : posY += speed / 2;
  }
  if (map.getMap()[(getPosX()) / tileSize + getPosY() / tileSize * map.getWidth()] == TP_RIGHT)
    setPosX(Utils::getStartX(map, TP_LEFT, tileSize));
  else if (map.getMap()[(getPosX() + tileSize) / tileSize + getPosY() / tileSize * map.getWidth()] == TP_LEFT)
    setPosX(Utils::getStartX(map, TP_RIGHT, tileSize));
}

void Ghost::find_next_move(Map & map, int idx_case_ghost, int idx_goal, int tileSize)
{
  int * mapi = map.getMap();
  int min = 5000;
  int calc;
  InputButton::id_button save = my_button;

  if (mapi[idx_case_ghost] == 46)
    inBox = false;
  if (hasBeenEat == true && idx_goal == idx_case_ghost)
    {
      hasBeenEat = false;
      changeDir = true;
      inBox = true;
      state_frightened = false;
    }
  if ((idx_case_ghost / map.getWidth()) - 1 >= 0 && isWalkable(mapi[idx_case_ghost - map.getWidth()]) && my_button != InputButton::DOWN)
  {
    calc = sqrt(pow((idx_case_ghost - map.getWidth()) % map.getWidth() * tileSize - idx_goal % map.getWidth() * tileSize, 2) + pow((idx_case_ghost - map.getWidth()) / map.getWidth() * tileSize - idx_goal / map.getWidth() * tileSize, 2));
    if (calc < min)
    {
      min = calc;
      save = InputButton::UP;
    }
  }
  if ((idx_case_ghost % map.getWidth()) - 1 >= 0 && isWalkable(mapi[idx_case_ghost - 1]) && my_button != InputButton::RIGHT)
  {
    calc = sqrt(pow((idx_case_ghost - 1) % map.getWidth() * tileSize - idx_goal % map.getWidth() * tileSize, 2) + pow((idx_case_ghost - 1) / map.getWidth() * tileSize - idx_goal / map.getWidth() * tileSize, 2));
    if (calc < min)
    {
      min = calc;
      save = InputButton::LEFT;
    }
  }
  if ((idx_case_ghost / map.getWidth()) + 1 < map.getHeight() && isWalkable(mapi[idx_case_ghost + map.getWidth()]) && my_button != InputButton::UP)
  {
    calc = sqrt(pow((idx_case_ghost + map.getWidth()) % map.getWidth() * tileSize - idx_goal % map.getWidth() * tileSize, 2) + pow((idx_case_ghost + map.getWidth()) / map.getWidth() * tileSize - idx_goal / map.getWidth() * tileSize, 2));
    if (calc < min)
    {
      min = calc;
      save = InputButton::DOWN;
    }
  }
  if ((idx_case_ghost % map.getWidth()) + 1 < map.getWidth() && isWalkable(mapi[idx_case_ghost + 1]) && my_button != InputButton::LEFT)
  {
    calc = sqrt(pow((idx_case_ghost + 1) % map.getWidth() * tileSize - idx_goal % map.getWidth() * tileSize, 2) + pow((idx_case_ghost + 1) / map.getWidth() * tileSize - idx_goal / map.getWidth() * tileSize, 2));
    if (calc < min)
    {
      min = calc;
      save = InputButton::RIGHT;
    }
  }
  if (changeDir)
  {
    if (my_button == InputButton::LEFT)
      move(map, InputButton::RIGHT, tileSize);
    else if (my_button == InputButton::RIGHT)
      move(map, InputButton::LEFT, tileSize);
    else if (my_button == InputButton::UP)
      move(map, InputButton::DOWN, tileSize);
    else if (my_button == InputButton::DOWN)
      move(map, InputButton::UP, tileSize);
    else
      move(map, save, tileSize);
    changeDir = false;
    return;
  }
  if ((idx_case_ghost == 8 + 8 * map.getWidth() || idx_case_ghost == 10 + 8 * map.getWidth() || idx_case_ghost == 8 + 16 * map.getWidth() || idx_case_ghost == 10 + 16 * map.getWidth()) && (my_button == InputButton::RIGHT || my_button == InputButton::LEFT))
    {
      move(map, my_button, tileSize);
      return;
    }
  if (name == "Red" && my_button == InputButton::UNDEF)
  {
    my_button = InputButton::LEFT;
    move(map, my_button, tileSize);
    return;
  }
  move(map, save, tileSize);
}

void Ghost::goal_red(Map & map, const PacmanEntity & pacman, int tileSize)
{
  if (hasBeenEat)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 9 + 10 * map.getWidth(), tileSize);
    return;
  }
  if (inBox)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 46, tileSize);
    return;
  }
  if (!frightened)
  {
    if (search)
      find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), (pacman.getPosX()) / tileSize + (pacman.getPosY()) / tileSize * map.getWidth(), tileSize);
    else
      find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 36, tileSize);
  }
  else
    randomMove(map, tileSize);
}

void Ghost::goal_pink(Map & map, const PacmanEntity & pacman, int tileSize, InputButton::id_button but)
{
  int idx_pacman = (pacman.getPosX()) / tileSize + (pacman.getPosY()) / tileSize * map.getWidth();
  int less;

  if (hasBeenEat)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 9 + 10 * map.getWidth(), tileSize);
    return;
  }
  if (inBox)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 46, tileSize);
    return;
  }
  if (!frightened)
  {
    if (search)
    {
      if (but == InputButton::LEFT)
      {
        less = ((idx_pacman % map.getWidth()) - 2 > 0 && isWalkable(map.getMap()[idx_pacman - 2])) ?
          2 : ((idx_pacman % map.getWidth()) - 1 >= 0 && isWalkable(map.getMap()[idx_pacman - 1])) ?
          1 : 0;
        find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), idx_pacman - less, tileSize);
      }
      else if (but == InputButton::RIGHT)
      {
        less  = ((idx_pacman % map.getWidth()) + 2 < map.getWidth() && isWalkable(map.getMap()[idx_pacman + 2])) ?
          2 : ((idx_pacman % map.getWidth()) + 1 <= map.getWidth() && isWalkable(map.getMap()[idx_pacman + 1])) ?
          1 : 0;
        find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), idx_pacman - less, tileSize);
      }
      else if (but == InputButton::UP)
      {
        idx_pacman = (pacman.getPosX() - 2 * tileSize) / tileSize + (pacman.getPosY() - 2 * tileSize) / tileSize * map.getWidth();

        if ((idx_pacman / map.getWidth()) > 0 && isWalkable(map.getMap()[idx_pacman]))
        {
          find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), idx_pacman, tileSize);
          return;
        }

        idx_pacman = (pacman.getPosX()) / tileSize + (pacman.getPosY()) / tileSize * map.getWidth();

        find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), idx_pacman, tileSize);
      }
      else if (but == InputButton::DOWN)
      {
        less = ((idx_pacman / map.getWidth()) + 2 < map.getHeight() && isWalkable(map.getMap()[idx_pacman + 2 * map.getWidth()])) ?
          2 * map.getWidth() : ((idx_pacman / map.getWidth()) + 1 <= map.getHeight() && isWalkable(map.getMap()[idx_pacman + map.getWidth()])) ?
          map.getWidth() : 0;
          find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), idx_pacman + less, tileSize);
      }
    }
    else
      find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), 20, tileSize);
  }
  else
    randomMove(map, tileSize);
}

void Ghost::goal_blue(const PacmanEntity & pacman, const Ghost & red, Map & map, int tileSize)
{
  int x_goal;
  int y_goal;

  if (hasBeenEat)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 9 + 10 * map.getWidth(), tileSize);
    return;
  }
  if (inBox)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 46, tileSize);
    return;
  }
  if (!frightened)
  {
    if (search)
    {
      for (int percent = 100 ; percent > 0 ; --percent)
      {
        x_goal = pacman.getPosX() + (pacman.getPosX() - red.getPosX()) * percent / 100;
        y_goal = pacman.getPosY() + (pacman.getPosY() - red.getPosY()) * percent / 100;
        if (0 < x_goal / tileSize && x_goal / tileSize < map.getWidth() && 0 < y_goal / tileSize && y_goal / tileSize < map.getWidth() && isWalkable(map.getMap()[(x_goal / tileSize) + (y_goal  / tileSize) * map.getWidth()]))
        {
          find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), (x_goal / tileSize) + (y_goal  / tileSize) * map.getWidth(), tileSize);
          return;
        }
      }
      find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), (x_goal / tileSize) + (y_goal  / tileSize) * map.getWidth(), tileSize);
    }
    else
      find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), 1 + 20 * map.getWidth(), tileSize);
  }
  else
    randomMove(map, tileSize);
}

void Ghost::goal_marron(const PacmanEntity & pacman, Map & map, int tileSize)
{
  if (hasBeenEat)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 9 + 10 * map.getWidth(), tileSize);
    return;
  }
  if (inBox)
  {
    find_next_move(map, (getPosX()) / tileSize + (getPosY()) / tileSize * map.getWidth(), 46, tileSize);
    return;
  }
  if (!frightened)
  {
    if (sqrt(pow(pacman.getPosX() - getPosX(), 2) + pow(pacman.getPosY() - getPosY(), 2)) > tileSize * 4)
      find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), pacman.getPosX() / tileSize + pacman.getPosY() / tileSize * map.getWidth(), tileSize);
    else
      find_next_move(map, (getPosX()) / tileSize + getPosY() / tileSize * map.getWidth(), 17 + 20 * map.getWidth(), tileSize);
  }
  else
    randomMove(map, tileSize);}

void Ghost::randomMove(Map & map, int tileSize)
{
  std::vector<InputButton::id_button> save;
  int * mapi = map.getMap();
  int idx_case_ghost = getPosX() / tileSize + getPosY() / tileSize * map.getWidth();

  if ((idx_case_ghost / map.getWidth()) - 1 > 0 && isWalkable(mapi[idx_case_ghost - map.getWidth()]) && my_button != InputButton::DOWN)
    save.push_back(InputButton::UP);
  if ((idx_case_ghost % map.getWidth()) - 1 > 0 && isWalkable(mapi[idx_case_ghost - 1]) && my_button != InputButton::RIGHT)
    save.push_back(InputButton::LEFT);
  if ((idx_case_ghost / map.getWidth()) + 1 < map.getHeight() && isWalkable(mapi[idx_case_ghost + map.getWidth()]) && my_button != InputButton::UP)
    save.push_back(InputButton::DOWN);
  if ((idx_case_ghost % map.getWidth()) + 1 < map.getWidth() && isWalkable(mapi[idx_case_ghost + 1]) && my_button != InputButton::LEFT)
    save.push_back(InputButton::RIGHT);
  if (!save.empty())
    move(map, save[rand() % (save.size() + 1)], tileSize);
  else
    move(map, my_button, tileSize);
}

void Ghost::setState(bool new_state)
{
  state = new_state;
}

bool Ghost::getState() const
{
  return state;
}

std::string Ghost::getSprite() const
{
  std::string * dir = new std::string[20];
  std::string   state_str;

  dir[InputButton::UNDEF] = "Left";
  dir[InputButton::LEFT] = "Left";
  dir[InputButton::RIGHT] = "Right";
  dir[InputButton::UP] = "Up";
  dir[InputButton::DOWN] = "Down";

  state_str = (state) ? "True" : "False";
  if (frightened && state_frightened)
    return ("White" + std::string("Ghost") + state_str);
  if (frightened)
    return ("Frightened" + std::string("Ghost") + state_str);
  if (hasBeenEat)
    return ("Eyes");
  return (name + std::string("Ghost") + dir[my_button] + state_str);
}

bool Ghost::isFrightened()
{
  return frightened;
}

InputButton::id_button Ghost::getWay() const
{
  return my_button;
}

void Ghost::setSearch(bool new_search)
{
  search = new_search;
  if (!search)
    changeDir = true;
}

void Ghost::setFrightened(bool state)
{
  frightened = state;
}

void Ghost::setStateFrightened(bool state)
{
  state_frightened = state;
}

void Ghost::setInBox(bool state)
{
  inBox = state;
}

bool Ghost::getStateFrightened() const
{
  return state_frightened;
}

bool Ghost::beingEat() const
{
  return eat;
}

void Ghost::setBeingEat(bool new_state)
{
  eat = new_state;
}

bool Ghost::isEaten() const
{
  return hasBeenEat;
}

void Ghost::setHasBeenEat(bool new_state)
{
  if (new_state == true)
    frightened = false;
  hasBeenEat = new_state;
}

void Ghost::setSpeed(int new_speed)
{
  speed = new_speed;
}
