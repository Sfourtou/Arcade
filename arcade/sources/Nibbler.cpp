#include <map>
#include <math.h>
#include "arcade.hh"
#include "Nibbler.hh"
#include "Protocol.hpp"
#include "Utils.hh"
#include <string.h>

Nibbler::Nibbler() :
AGame("Nibbler"), init(false), button(InputButton::UNDEF), hasCollision(false), timeEnable(true)
{

}

Nibbler::~Nibbler()
{

}

bool Nibbler::gere_collision_x(int col)
{
  int * mapi = map.getMap();
   for (int y = 0; y != accuracy ; ++y)
   {
     int nb = mapi[(snake.getPosX() + col) / accuracy + (snake.getPosY() + y) / accuracy * map.getWidth()];
     if (nb != 0 && nb != 45)
       return false;
  }
  return true;
}

bool Nibbler::gere_collision_y(int col)
{
   int * mapi = map.getMap();
   for (int x = 0; x != accuracy ; ++x)
   {
     int nb = mapi[(snake.getPosX() + x) / accuracy + (snake.getPosY() + col) / accuracy * map.getWidth()];
     if (nb != 0 && nb != 45)
       return false;
   }
   return true;
}

void Nibbler::move()
{
  bool left = gere_collision_x(-1);
  bool right = gere_collision_x(accuracy);
  bool up = gere_collision_y(-1);
  bool down = gere_collision_y(accuracy);

  switch (button)
   {
     case InputButton::LEFT:
       if (!left)
       {
         hasCollision = true;
         break;
       }
       snake.setWay(InputButton::LEFT);
       snake.move(snake.getPosX() - accuracy, snake.getPosY());
       break;
     case InputButton::RIGHT:
     if (!right)
     {
       hasCollision = true;
       break;
     }
     snake.setWay(InputButton::RIGHT);
     snake.move(snake.getPosX() + accuracy, snake.getPosY());
      break;
     case InputButton::UP:
     if (!up) {
       hasCollision = true;
       break;
     }
     snake.setWay(InputButton::UP);
     snake.move(snake.getPosX(), snake.getPosY() - accuracy);
     break;
    case InputButton::DOWN:
    if (!down)
    {
      hasCollision = true;
      break;
    }
    snake.setWay(InputButton::DOWN);
     snake.move(snake.getPosX(), snake.getPosY() + accuracy);
       break;
   }
}

void Nibbler::initSnakeEntity()
{
  snake.setWay(InputButton::UNDEF);
  snake.initSnakeBody(Utils::getStartX(map, START_CASE, accuracy), Utils::getStartY(map, START_CASE, accuracy), accuracy);
}

void Nibbler::loadTextures(IDynLib *lib)
{
  lib->addSprite("GreenSnakeBodyDownToRight", "Sprites/snake-graphics.png", 0, 0);
  lib->addSprite("GreenSnakeBodyX", "Sprites/snake-graphics.png", 1 * 128, 0);
  lib->addSprite("GreenSnakeBodyDownToLeft", "Sprites/snake-graphics.png", 2 * 128, 0);
  lib->addSprite("GreenSnakeHeadUp", "Sprites/snake-graphics.png", 3 * 128, 0);
  lib->addSprite("GreenSnakeHeadRight", "Sprites/snake-graphics.png", 4 * 128, 0);

  lib->addSprite("GreenSnakeBodyUpToRight", "Sprites/snake-graphics.png", 0, 128);
  lib->addSprite("GreenSnakeBodyY", "Sprites/snake-graphics.png", 2 * 128, 128);
  lib->addSprite("GreenSnakeHeadLeft", "Sprites/snake-graphics.png", 3 * 128, 128);
  lib->addSprite("GreenSnakeHeadDown", "Sprites/snake-graphics.png", 4 * 128, 128);
  lib->addSprite("GreenSnakeBodyUpToLeft", "Sprites/snake-graphics.png", 2 * 128, 128 * 2);

  lib->addSprite("GreenSnakeQUp", "Sprites/snake-graphics.png", 3 * 128, 128 * 2);
  lib->addSprite("GreenSnakeQRight", "Sprites/snake-graphics.png", 4 * 128, 128 * 2);
  lib->addSprite("GreenSnakeQLeft", "Sprites/snake-graphics.png", 3 * 128, 128 * 3);
  lib->addSprite("GreenSnakeQDown", "Sprites/snake-graphics.png", 4 * 128, 128 * 3);
  lib->addSprite("RedFruit", "Sprites/snake-graphics.png", 0 * 128, 128 * 3);

  lib->setNameTextureMap("Sprites/chompermazetiles" + std::to_string(accuracy) + ".png");
  lib->addFont("text" ,"font/crackman.ttf");
  lib->addFont("score" ,"font/Square.ttf");

  lib->addSound("nibbler", "sounds/nibbler_music.ogg");

}

const std::vector<std::string> & Nibbler::getPosCharacters()
{
  posCharacters.clear();
  getCharacters();
  for (std::vector<ACharacter *>::iterator it = characters.begin() ; it != characters.end() ; ++it)
  {
    posCharacters.push_back(std::to_string((*it)->getPosX()) + " " + std::to_string((*it)->getPosY()) + " " + (*it)->getSprite());
  }
  return posCharacters;
}

const std::vector<ACharacter *> & Nibbler::getCharacters()
{
  characters.clear();
  const std::vector<SnakeBody *> charac = snake.getBody();
  for (std::vector<SnakeBody *>::const_iterator it = charac.begin(); it != charac.end(); ++it)
    characters.push_back(*it);
  characters.push_back(&apple);
  return characters;
}

void Nibbler::gereKey(InputButton::id_button id)
{
  switch(id)
  {
    case InputButton::LEFT:
      if (snake.getWay() != InputButton::RIGHT)
      button = InputButton::LEFT;
    break;
    case InputButton::RIGHT:
      if (snake.getWay() != InputButton::LEFT)
      button = InputButton::RIGHT;
    break;
    case InputButton::UP:
      if (snake.getWay() != InputButton::DOWN)
      button = InputButton::UP;
    break;
    case InputButton::DOWN:
      if (snake.getWay() != InputButton::UP && snake.getWay() != InputButton::UNDEF)
      button = InputButton::DOWN;
    break;
  }
}

void Nibbler::fruitPop()
{
  int * mappy = map.getMap();
  int width = map.getWidth();
  int height = map.getHeight();
  int i;

  while (42)
  {
    i = rand() % (width * height);
    if ((mappy[i] == 0 || mappy[i] == 45) && !snake.checkCollision((i % width) * accuracy, (i / (width)) * accuracy))
    {
      apple.setPosX((i % width) * accuracy);
      apple.setPosY((i / (width)) * accuracy);
      return;
    }
  }
}

void Nibbler::init_game()
{
  score.load("scores/Nibbler.score", 10);
  if (!init)
  {
     score.reset();
    map.loadMap("Maps/03.map");
    if (timeEnable)
      timerMoving.startTime();
    init = true;
  }
  score.reset();
  hasCollision = false;
  initSnakeEntity();
  fruitPop();
  button = InputButton::UNDEF;
  snake.setWay(InputButton::UNDEF);
}

void Nibbler::checkFruit()
{
  if (snake.getPosX() == apple.getPosX() && snake.getPosY() == apple.getPosY())
  {
    score.add(10);
    fruitPop();
    snake.growUp(accuracy);
  }
}

bool Nibbler::playGame(const std::string & playerName)
{
  bool canDisplay = false;
  // sounds.clear();
  //
  // sounds.push_back("nibbler");
  if ((!timerMoving.isPaused() && timerMoving.getTimeElapsed() > 100000) || !timeEnable)
  {
    if (hasCollision)
    {
      score.save("scores/Nibbler.score", playerName);
      score.reset();
      sleep(1);
      init_game();
    }
      move();
      checkFruit();
    if (snake.checkCollision(snake.getPosX(), snake.getPosY()))
      hasCollision = true;

    timerMoving.resetTime();
    canDisplay = true;
  }
  return canDisplay;
}

void Nibbler::pause()
{
  timerMoving.paused(!timerMoving.isPaused());
}

void Nibbler::setTimeEnable(bool time)
{
  timeEnable = time;
}

int Nibbler::getLifes() const
{
  return 0;
}

uint16_t *transform_map(int *map, int size)
{
  uint16_t *map2 = new uint16_t[size];
  int i;

  i = -1;
  //map2 = (uint16_t *)malloc(size * sizeof(uint16_t));
  while (++i < size)
  {
    if (map[i] != 0 && map[i] != 45)
      map2[i] = (uint16_t)arcade::TileType::BLOCK;
    else
      map2[i] = (uint16_t)arcade::TileType::EMPTY;
  }
  return (map2);
}

void setAppleOnMap(uint16_t *map, int width, int posX, int posY)
{
  map[posX + (posY * width)] = (int)arcade::TileType::POWERUP;
}

arcade::Position *getcharacter(Nibbler * &game, int &size)
{
  std::vector<ACharacter *> characters = game->getCharacters();
  arcade::Position *position = new arcade::Position[characters.size() - 1];
//  Position *position = (Position *)malloc(sizeof(Position) * characters.size() - 1);
  int i = -1;
  size = characters.size() - 1;
  for (std::vector<ACharacter *>::iterator it = characters.begin(); it != characters.end(); ++it)
  {
    if (std::next(it, 1) != characters.end())
    {
      position[++i].x = (*it)->getPosX() / 24;
      position[i].y = (*it)->getPosY() / 24;
    }
  }
  return position;
}

void Nibbler::setInit(bool state) {
   init = state;
}

void get_map(Nibbler * & game)
{
  Map map = game->getMap();

  int size = sizeof(arcade::GetMap) + (sizeof(uint16_t) * (map.getWidth() * map.getHeight()));
  uint16_t *mappy = transform_map(map.getMap(), map.getWidth() * map.getHeight());

  std::vector<ACharacter *> characters = game->getCharacters();
  setAppleOnMap(mappy, map.getWidth(), (*characters.rbegin())->getPosX() / 24, (*characters.rbegin())->getPosY() / 24);
  arcade::GetMap *map2 = (arcade::GetMap *)malloc(size);
  map2->type = arcade::CommandType::GET_MAP;
  map2->width = map.getWidth();
  map2->height = map.getHeight();
  memcpy(&map2->tile[0], &mappy[0], (sizeof(uint16_t) * (map.getWidth() * map.getHeight())));
  write(1, map2, size);
  free(map2);
  delete(mappy);
}

void getWhereAmI(Nibbler * & game)
{
  int sizeSnake;
  arcade::Position *position = getcharacter(game, sizeSnake);
  int size = sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * sizeSnake;
  arcade::WhereAmI *ami = (arcade::WhereAmI *)malloc(size);
  ami->type = arcade::CommandType::WHERE_AM_I;
  ami->lenght = sizeSnake;
  memcpy(&ami->position[0], &position[0], sizeof(arcade::Position) * sizeSnake);
  write(1, ami, size);
  free(ami);
  delete position;
}

extern "C"
{
  void Play(void)
  {
    arcade::CommandType commandtype;
    Nibbler *game = new Nibbler();
    game->setTimeEnable(false);
    game->setAccuracy(24);
    game->init_game();
    game->gereKey(InputButton::UP);
    while (42)
    {
      read(0,  &commandtype, sizeof(arcade::CommandType));
      switch(commandtype)
      {
        case arcade::CommandType::WHERE_AM_I:
          getWhereAmI(game);
        break;
        case arcade::CommandType::GET_MAP:
          get_map(game);
        break;
        case arcade::CommandType::GO_UP:
          game->gereKey(InputButton::UP);
        break;
        case arcade::CommandType::GO_DOWN:
          game->gereKey(InputButton::DOWN);
        break;
        case arcade::CommandType::GO_RIGHT:
          game->gereKey(InputButton::RIGHT);
        break;
        case arcade::CommandType::GO_LEFT:
          game->gereKey(InputButton::LEFT);
        break;
        case arcade::CommandType::GO_FORWARD:
        break;
        case arcade::CommandType::PLAY:
        game->playGame("");
        break;
      }
    }
  }
  AGame * create_game()
  {
    return new Nibbler();
  }
}
