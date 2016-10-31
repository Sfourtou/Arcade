/*
** PacMan.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 23:39:08 2016 fourto_s
// Last update Sun Apr  3 01:01:05 2016 marcha_0
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "arcade.hh"
#include "PacMan.hh"
#include "Utils.hh"
#include "Protocol.hpp"

PacMan::PacMan() :
  AGame("Pacman"), red(Ghost("Red")), pink(Ghost("Orange")), blue(Ghost("Blue")), marron(Ghost("Marron")), init(false), time_enabled(true)
{
}

PacMan::~PacMan()
{
}

void PacMan::loadTextures(IDynLib * lib)
{
  lib->addSprite("pacRightFalse", "Sprites/chompersprites.png", 10 * 128, 0);
  lib->addSprite("pacRightTrue", "Sprites/chompersprites.png", 11 * 128, 0);
  lib->addSprite("pacUpFalse", "Sprites/chompersprites.png", 10 * 128, 128 * 3);
  lib->addSprite("pacUpTrue", "Sprites/chompersprites.png", 11 * 128, 128 * 3);
  lib->addSprite("pacLeftFalse", "Sprites/chompersprites.png", 10 * 128, 128 * 2);
  lib->addSprite("pacLeftTrue", "Sprites/chompersprites.png", 11 * 128, 128 * 2);
  lib->addSprite("pacDownFalse", "Sprites/chompersprites.png", 10 * 128, 128);
  lib->addSprite("pacDownTrue", "Sprites/chompersprites.png", 11 * 128, 128);
  lib->addSprite("pacBlack", "Sprites/chompersprites.png", 13 * 128, 128 * 3);

  lib->addSprite("RedGhostRightFalse", "Sprites/chompersprites.png", 0 * 128, 0);
  lib->addSprite("RedGhostRightTrue", "Sprites/chompersprites.png", 1 * 128, 0);
  lib->addSprite("RedGhostUpFalse", "Sprites/chompersprites.png", 0 * 128, 128 * 3);
  lib->addSprite("RedGhostUpTrue", "Sprites/chompersprites.png", 1 * 128, 128 * 3);
  lib->addSprite("RedGhostLeftFalse", "Sprites/chompersprites.png", 0 * 128, 128 * 2);
  lib->addSprite("RedGhostLeftTrue", "Sprites/chompersprites.png", 1 * 128, 128 * 2);
  lib->addSprite("RedGhostDownFalse", "Sprites/chompersprites.png", 0 * 128, 128);
  lib->addSprite("RedGhostDownTrue", "Sprites/chompersprites.png", 1 * 128, 128);

  lib->addSprite("OrangeGhostRightFalse", "Sprites/chompersprites.png", 4 * 128, 0);
  lib->addSprite("OrangeGhostRightTrue", "Sprites/chompersprites.png", 5 * 128, 0);
  lib->addSprite("OrangeGhostUpFalse", "Sprites/chompersprites.png", 4 * 128, 128 * 3);
  lib->addSprite("OrangeGhostUpTrue", "Sprites/chompersprites.png", 5 * 128, 128 * 3);
  lib->addSprite("OrangeGhostLeftFalse", "Sprites/chompersprites.png", 4 * 128, 128 * 2);
  lib->addSprite("OrangeGhostLeftTrue", "Sprites/chompersprites.png", 5 * 128, 128 * 2);
  lib->addSprite("OrangeGhostDownFalse", "Sprites/chompersprites.png", 4 * 128, 128);
  lib->addSprite("OrangeGhostDownTrue", "Sprites/chompersprites.png", 5 * 128, 128);

  lib->addSprite("BlueGhostRightFalse", "Sprites/chompersprites.png", 6 * 128, 0);
  lib->addSprite("BlueGhostRightTrue", "Sprites/chompersprites.png", 7 * 128, 0);
  lib->addSprite("BlueGhostUpFalse", "Sprites/chompersprites.png", 6 * 128, 128 * 3);
  lib->addSprite("BlueGhostUpTrue", "Sprites/chompersprites.png", 7 * 128, 128 * 3);
  lib->addSprite("BlueGhostLeftFalse", "Sprites/chompersprites.png", 6 * 128, 128 * 2);
  lib->addSprite("BlueGhostLeftTrue", "Sprites/chompersprites.png", 7 * 128, 128 * 2);
  lib->addSprite("BlueGhostDownFalse", "Sprites/chompersprites.png", 6 * 128, 128);
  lib->addSprite("BlueGhostDownTrue", "Sprites/chompersprites.png", 7 * 128, 128);

  lib->addSprite("MarronGhostRightFalse", "Sprites/chompersprites.png", 2 * 128, 0);
  lib->addSprite("MarronGhostRightTrue", "Sprites/chompersprites.png", 3 * 128, 0);
  lib->addSprite("MarronGhostUpFalse", "Sprites/chompersprites.png", 2 * 128, 128 * 3);
  lib->addSprite("MarronGhostUpTrue", "Sprites/chompersprites.png", 3 * 128, 128 * 3);
  lib->addSprite("MarronGhostLeftFalse", "Sprites/chompersprites.png", 2 * 128, 128 * 2);
  lib->addSprite("MarronGhostLeftTrue", "Sprites/chompersprites.png", 3 * 128, 128 * 2);
  lib->addSprite("MarronGhostDownFalse", "Sprites/chompersprites.png", 2 * 128, 128);
  lib->addSprite("MarronGhostDownTrue", "Sprites/chompersprites.png", 3 * 128, 128);

  lib->addSprite("FrightenedGhostTrue", "Sprites/chompersprites.png", 12 * 128, 0);
  lib->addSprite("FrightenedGhostFalse", "Sprites/chompersprites.png", 13 * 128, 0);

  lib->addSprite("WhiteGhostFalse", "Sprites/chompersprites.png", 12 * 128, 128);
  lib->addSprite("WhiteGhostTrue", "Sprites/chompersprites.png", 13 * 128, 128);

  lib->addSprite("Eyes", "Sprites/chompersprites.png", 13 * 128, 128 * 2);

  lib->setNameTextureMap("Sprites/chompermazetiles" + std::to_string(accuracy) + ".png");
  lib->setNameTextureLife("Sprites/pacman_24.png");

  lib->addFont("text" ,"font/crackman.ttf");
  lib->addFont("score" ,"font/Square.ttf");

  lib->addSound("pacman", "sounds/nibbler_music.ogg");
}

bool PacMan::gere_collision_x(int col)
{
  int * mapi = map.getMap();
  for (int y = 0; y != accuracy ; ++y)
  {
    int nb = mapi[(pacman.getPosX() + col) / accuracy + (pacman.getPosY() + y) / accuracy * map.getWidth()];
    if (nb != 0 && nb != 30 && nb != 45 && nb != 29 && nb != 28 && nb != 98 && nb != 99 && nb != 90 && nb != START_RED)
      return false;
  }
  return true;
}

bool PacMan::gere_collision_y(int col)
{
  int * mapi = map.getMap();
  for (int x = 0; x != accuracy ; ++x)
  {
    int nb = mapi[(pacman.getPosX() + x) / accuracy + (pacman.getPosY() + col) / accuracy * map.getWidth()];
    if (nb != 0 && nb != 30 && nb != 45 && nb != 29 && nb != 28 && nb != 98 && nb != 99 && nb != 90 && nb != START_RED)
      return false;
  }
  return true;
}

void PacMan::move()
{
  int * mapi = map.getMap();
  bool left = gere_collision_x(-SPEED);
  bool right = gere_collision_x(accuracy);
  bool up = gere_collision_y(-SPEED);
  bool down = gere_collision_y(accuracy);

  if (pacman.getIdButton() == InputButton::LEFT && left)
  {
    pacman.setPosX(pacman.getPosX() - SPEED);
    pacman.setWay(InputButton::LEFT);
  }
  else if (pacman.getIdButton() == InputButton::RIGHT && right)
  {
    pacman.setPosX(pacman.getPosX() + SPEED);
    pacman.setWay(InputButton::RIGHT);
  }
  else if (pacman.getIdButton() == InputButton::UP && up)
  {
    pacman.setPosY(pacman.getPosY() - SPEED);
    pacman.setWay(InputButton::UP);
  }
  else if (pacman.getIdButton() == InputButton::DOWN && down)
  {
    pacman.setPosY(pacman.getPosY() + SPEED);
    pacman.setWay(InputButton::DOWN);
  }
  else
  {
    if (pacman.getWay() == InputButton::LEFT && left)
      pacman.setPosX(pacman.getPosX() - SPEED);
    else if (pacman.getWay() == InputButton::RIGHT && right)
      pacman.setPosX(pacman.getPosX() + SPEED);
    else if (pacman.getWay() == InputButton::UP && up)
      pacman.setPosY(pacman.getPosY() - SPEED);
    else if (pacman.getWay() == InputButton::DOWN && down)
      pacman.setPosY(pacman.getPosY() + SPEED);
  }
  if (mapi[(pacman.getPosX() + accuracy) / accuracy + (pacman.getPosY() / accuracy * map.getWidth())] == TP_LEFT)
    pacman.setPosX(Utils::getStartX(map, TP_RIGHT, accuracy));
  else if (mapi[(pacman.getPosX() / accuracy) + (pacman.getPosY() / accuracy * map.getWidth())] == TP_RIGHT)
    pacman.setPosX(Utils::getStartX(map, TP_LEFT, accuracy));
}

void PacMan::gereKey(InputButton::id_button id)
{
  int * mapi = map.getMap();
  bool left = gere_collision_x(-SPEED);
  bool right = gere_collision_x(accuracy);
  bool up = gere_collision_y(-SPEED);
  bool down = gere_collision_y(accuracy);

  if (id == InputButton::LEFT)
  {
    pacman.setIdButton(InputButton::LEFT);
    (left) ? pacman.setWay(InputButton::LEFT) : pacman.setWay(pacman.getWay());
  }
  else if (id == InputButton::RIGHT)
  {
    pacman.setIdButton(InputButton::RIGHT);
    (right) ? pacman.setWay(InputButton::RIGHT) : pacman.setWay(pacman.getWay());
  }
  else if (id == InputButton::UP)
  {
    pacman.setIdButton(InputButton::UP);
    (up) ? pacman.setWay(InputButton::UP) : pacman.setWay(pacman.getWay());
  }
  else if (id == InputButton::DOWN)
  {
    pacman.setIdButton(InputButton::DOWN);
    (down) ? pacman.setWay(InputButton::DOWN) : pacman.setWay(pacman.getWay());
  }
}

void changeBigPacgum(Map & map)
{
  for (int i = 0 ; i < map.getWidth() * map.getHeight() ; ++i)
  {
    if (map.getMap()[i] == BIG_PAC_GUM)
      map.getMap()[i] = BIG_PAC_GUM_LIGHT;
    else if (map.getMap()[i] == BIG_PAC_GUM_LIGHT)
      map.getMap()[i] = BIG_PAC_GUM;
  }
}

void PacMan::init_game()
{
  score.load("scores/Pacman.score", 10);

  if (init == false)
  {
    timer_moving.startTime();
    timer_animated.startTime();
    timer_state.startTime();
    timer_ghost.startTime();
    score.reset();
    map.loadMap("Maps/01.map");
    initGhosts();
    initPacmanEntity();
    init = true;
  }
  if (time_enabled)
  {
    timer_moving.startTime();
    timer_animated.startTime();
    timer_state.startTime();
    timer_ghost.startTime();
  }
}

void PacMan::manageScore()
{
  int idx = (pacman.getPosX() + accuracy / 2) / accuracy + (pacman.getPosY() + accuracy / 2) / accuracy * map.getWidth();

  if (map.getMap()[idx] == 30)
  {
    score.add(10);
    map.getMap()[idx] = 0;
  }
  else if (map.getMap()[idx] == 29 || map.getMap()[idx] == 28)
  {
    if (!red.isEaten())
    {
      red.setFrightened(true);
      red.setStateFrightened(false);
    }
    if (!pink.isEaten())
    {
      pink.setFrightened(true);
      pink.setStateFrightened(false);
    }
    if (!blue.isEaten())
    {
      blue.setFrightened(true);
      blue.setStateFrightened(false);
    }
    if (!marron.isEaten())
    {
      marron.setFrightened(true);
      marron.setStateFrightened(false);
    }
    timer_frightened.startTime();
    score.add(50);
    map.getMap()[idx] = 0;
  }
}

bool PacMan::playGame(const std::string & playerName)
{
  std::vector<Ghost *> ghosts;
  bool display = false;
  static int time_chase = 7;
  static int roll = 0;

  // sounds.clear();
  // sounds.push_back("pacman");

  ghosts.push_back(&red);
  ghosts.push_back(&pink);
  ghosts.push_back(&blue);
  ghosts.push_back(&marron);
  if (time_enabled == false || (!timer_moving.isPaused() && timer_moving.getTimeElapsed() > 15000))
  {
    move();
    display = true;
    if (pacman.getWay() != InputButton::UNDEF)
      calcPosGhosts();
    else
    {
      timer_ghost.startTime();
      timer_chase.startTime();
    }
    timer_moving.resetTime();
  }
  if (timer_frightened.getTimeElapsedSec() >= 10)
    GhostNoMoreFrightened();
  if (timer_state.getTimeElapsed() > 100000)
    changeStateCharacters();
  if (timer_animated.getTimeElapsed() > 300000)
  {
    changeBigPacgum(map);
    timer_animated.resetTime();
  }
  if (timer_chase.getTimeElapsedSec() == time_chase)
    changeGhostBehavior(roll, time_chase);
  if (pacman.touchedGhost(ghosts, accuracy) == true)
    {
      bool eat = hasEatGhost(ghosts);
      if (!eat)
      {
        timer_moving.paused(true);
        pacman.setLifes(pacman.getLifes() - 1);
        if (pacman.getLifes() == 0)
        {
          score.save("scores/Pacman.score", playerName);
          score.reset();
          pacman.setLifes(2);
          init = false;
        }
        reLaunchGame();
      }
    }
  manageScore();
  if (noMorePacGum())
  {
    map.loadMap("Maps/01.map");
    reLaunchGame();
  }
  return display;
}

void PacMan::initGhosts()
{
  red.setStartX(Utils::getStartX(map, START_RED, accuracy));
  red.setStartY(Utils::getStartY(map, START_RED, accuracy));
  pink.setStartX(Utils::getStartX(map, START_ORANGE, accuracy));
  pink.setStartY(Utils::getStartY(map, START_ORANGE, accuracy));
  blue.setStartX(Utils::getStartX(map, START_BLUE, accuracy));
  blue.setStartY(Utils::getStartY(map, START_BLUE, accuracy));
  marron.setStartX(Utils::getStartX(map, START_MARRON, accuracy));
  marron.setStartY(Utils::getStartY(map, START_MARRON, accuracy));

  red.setPosX(red.getStartX());
  red.setPosY(red.getStartY());
  pink.setPosX(pink.getStartX());
  pink.setPosY(pink.getStartY());
  blue.setPosX(blue.getStartX());
  blue.setPosY(blue.getStartY());
  marron.setPosX(marron.getStartX());
  marron.setPosY(marron.getStartY());



  red.setInBox(true);
  pink.setInBox(true);
  blue.setInBox(true);
  marron.setInBox(true);

  red.setFrightened(false);
  pink.setFrightened(false);
  blue.setFrightened(false);
  marron.setFrightened(false);

  red.setHasBeenEat(false);
  pink.setHasBeenEat(false);
  blue.setHasBeenEat(false);
  marron.setHasBeenEat(false);

  timer_ghost.startTime();
}

void PacMan::initPacmanEntity()
{
  pacman.setStartX(Utils::getStartX(map, START_CASE, accuracy));
  pacman.setStartY(Utils::getStartY(map, START_CASE, accuracy));

  pacman.setPosX(pacman.getStartX());
  pacman.setPosY(pacman.getStartY());
  pacman.setIdButton(InputButton::UNDEF);
  pacman.setWay(InputButton::UNDEF);
}

void PacMan::pause()
{
  timer_moving.paused(!timer_moving.isPaused());
  timer_frightened.paused(!timer_frightened.isPaused());
  timer_ghost.paused(!timer_ghost.isPaused());
  timer_state.paused(!timer_state.isPaused());
  timer_chase.paused(!timer_chase.isPaused());
}

bool PacMan::noMorePacGum()
{
  for (int y = 0 ; y < map.getHeight() ; ++y)
  {
    for (int x = 0 ; x < map.getWidth() ; ++x)
      {
        int nb = map.getMap()[x + y * map.getWidth()];
        if (nb == BIG_PAC_GUM || nb == BIG_PAC_GUM_LIGHT || nb == 30)
          return false;
      }
  }
  return true;
}

void PacMan::changeGhostBehavior(int & roll, int & time_chase)
{
  if (roll < 4 && time_chase == 20)
  {
    red.setSearch(false);
    pink.setSearch(false);
    marron.setSearch(false);
    blue.setSearch(false);
    time_chase = 7;
  }
  else if (roll < 7 && time_chase == 20)
  {
    red.setSearch(false);
    pink.setSearch(false);
    marron.setSearch(false);
    blue.setSearch(false);
    time_chase = 5;
  }
  else
  {
    red.setSearch(true);
    pink.setSearch(true);
    marron.setSearch(true);
    blue.setSearch(true);
    time_chase = 20;
  }
  ++roll;
  timer_chase.resetTime();
}

void PacMan::changeStateCharacters()
{
  pacman.setState(!pacman.getState());
  red.setState(!red.getState());
  pink.setState(!pink.getState());
  blue.setState(!blue.getState());
  marron.setState(!marron.getState());
  if (timer_frightened.getTimeElapsedSec() >= 7 && timer_frightened.getTimeElapsedSec() < 10)
  {
    red.setStateFrightened(!red.getStateFrightened());
    pink.setStateFrightened(!pink.getStateFrightened());
    blue.setStateFrightened(!blue.getStateFrightened());
    marron.setStateFrightened(!marron.getStateFrightened());
  }
  timer_state.resetTime();
}

void PacMan::GhostNoMoreFrightened()
{
  red.setFrightened(false);
  pink.setFrightened(false);
  blue.setFrightened(false);
  marron.setFrightened(false);

  red.setStateFrightened(false);
  pink.setStateFrightened(false);
  blue.setStateFrightened(false);
  marron.setStateFrightened(false);
}

void PacMan::calcPosGhosts()
{
  red.goal_red(map, pacman, accuracy);
  if (!timer_ghost.isPaused() && timer_ghost.getTimeElapsedSec() > 5)
    pink.goal_pink(map, pacman, accuracy, pacman.getWay());
  if (!timer_ghost.isPaused() && timer_ghost.getTimeElapsedSec() > 10)
    blue.goal_blue(pacman, red, map, accuracy);
  if (!timer_ghost.isPaused() && timer_ghost.getTimeElapsedSec() > 15)
    marron.goal_marron(pacman, map, accuracy);
}

bool PacMan::hasEatGhost(std::vector<Ghost *> ghosts)
{
  for (std::vector<Ghost *>::iterator it = ghosts.begin() ; it != ghosts.end() ; ++it)
  {
    if ((*it)->isEaten() && (*it)->beingEat())
      {
        int saveX = (*it)->getPosX();
        int saveY = (*it)->getPosY();

        (*it)->setPosX(-100);
        (*it)->setPosY(-100);
        score.add(200);
        (*it)->setPosX(saveX);
        (*it)->setPosY(saveY);
        (*it)->setBeingEat(false);
        return true;
      }
  }
  return false;
}

void PacMan::reLaunchGame()
{
  sleep(2);
  initGhosts();
  initPacmanEntity();
  timer_moving.paused(false);
  init_game();

}

const std::vector<std::string> & PacMan::getPosCharacters()
{
  posCharacters.clear();
  getCharacters();
  for (std::vector<ACharacter *>::iterator it = characters.begin() ; it != characters.end() ; ++it)
  {
    posCharacters.push_back(std::to_string((*it)->getPosX()) + " " + std::to_string((*it)->getPosY()) + " " + (*it)->getSprite());
  }
  return posCharacters;
}

const std::vector<ACharacter *> & PacMan::getCharacters()
{
  characters.clear();
  characters.push_back(&pacman);
  characters.push_back(&red);
  characters.push_back(&blue);
  characters.push_back(&pink);
  characters.push_back(&marron);
  return characters;
}

int PacMan::getLifes() const
{
  return pacman.getLifes();
}

void PacMan::setTimeEnabled(bool state)
{
  time_enabled = state;
}

void PacMan::setSpeedCharacters(int speed)
{
  pacman.setSpeed(speed);
  red.setSpeed(speed);
  blue.setSpeed(speed);
  marron.setSpeed(speed);
  pink.setSpeed(speed);
}

void PacMan::setInit(bool state)
{
   init = state;
}


void getWhereAmI(PacMan * & pac)
{
  //position x y pacman vector ACharatcer
  std::vector<ACharacter *> characters = pac->getCharacters();

  arcade::Position * pos_pac = new arcade::Position;

  pos_pac->x = characters[0]->getPosX() / 24;
  pos_pac->y = characters[0]->getPosY() / 24;

  int size = sizeof(arcade::WhereAmI) + sizeof(arcade::Position);
  arcade::WhereAmI * pos = (arcade::WhereAmI *)malloc(size);

  pos->type = arcade::CommandType::WHERE_AM_I;
  pos->lenght = 1;
  memcpy(&pos->position[0], &pos_pac[0], sizeof(arcade::Position));
  write(1, pos, size);
}

void getMap(PacMan * & pac)
{
  uint16_t * map = new uint16_t[pac->getMap().getWidth() * pac->getMap().getHeight()];

  int * mapi = pac->getMap().getMap();

  for (int y = 0 ; y < pac->getMap().getHeight() ; ++y)
  {
    for (int x = 0 ; x < pac->getMap().getWidth() ; ++x)
    {
      if (mapi[x + y * pac->getMap().getWidth()] == 50 || (mapi[x + y * pac->getMap().getWidth()] != 0 && mapi[x + y * pac->getMap().getWidth()] < 28))
        map[x + y * pac->getMap().getWidth()] = (uint16_t)arcade::TileType::BLOCK;
      else if (mapi[x + y * pac->getMap().getWidth()] == 28 || mapi[x + y * pac->getMap().getWidth()] == 29)
        map[x + y * pac->getMap().getWidth()] = (uint16_t)arcade::TileType::POWERUP;
      else
        map[x + y * pac->getMap().getWidth()] = (uint16_t)arcade::TileType::EMPTY;
    }
  }

  int size = sizeof(arcade::GetMap) + sizeof(uint16_t) * pac->getMap().getWidth() * pac->getMap().getHeight();
  arcade::GetMap * myMap = (arcade::GetMap *)malloc(size);

  myMap->type = arcade::CommandType::GET_MAP;
  myMap->width = pac->getMap().getWidth();
  myMap->height = pac->getMap().getHeight();

  memcpy(&myMap->tile[0], map, sizeof(uint16_t) * pac->getMap().getWidth() * pac->getMap().getHeight());
  write(1, myMap, size);
}

extern "C"
{
  void Play(void)
  {
    arcade::CommandType type;
    PacMan * pac = new PacMan;
    pac->setTimeEnabled(false);
    pac->setAccuracy(24);
    pac->init_game();
    pac->setSpeedCharacters(24);
    while (true)
    {
      read(0, &type, sizeof(arcade::CommandType));
      switch (type)
      {
        case arcade::CommandType::WHERE_AM_I:
          getWhereAmI(pac);
          break;
        case arcade::CommandType::GET_MAP:
	  getMap(pac);
    break;

        case arcade::CommandType::GO_UP:
          pac->gereKey(InputButton::UP); break;
        case arcade::CommandType::GO_DOWN:
          pac->gereKey(InputButton::DOWN); break;
        case arcade::CommandType::GO_LEFT:
          pac->gereKey(InputButton::LEFT); break;
        case arcade::CommandType::GO_RIGHT:
          pac->gereKey(InputButton::RIGHT); break;
        case arcade::CommandType::PLAY:
          pac->playGame("");
      }
    }
  }

  AGame * create_game()
  {
    return new PacMan();
  }

}
