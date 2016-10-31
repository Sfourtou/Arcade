#include "Centipede.hh"

Centipede::Centipede()
   : AGame("Centipede"), shoot(0), init(false), lifes(2), timeEnable(true)
{
}

Centipede::~Centipede()
{

}

void
Centipede::initPlayer()
{
   player.setStartX(Utils::getStartX(map, START_CASE, accuracy));
   player.setStartY(Utils::getStartY(map, START_CASE, accuracy));

   player.setPosX(player.getStartX());
   player.setPosY(player.getStartY());
   player.setIdButton(InputButton::UNDEF);
}

void
Centipede::initMushs()
{
   Mushroom *tmp;

   for (unsigned int i = 0; i <= 20; ++i)
   {
      tmp = new Mushroom();
      tmp->setStartX((rand() % (map.getWidth() - 2) + 1) * accuracy);
      tmp->setStartY((rand() % (map.getHeight() - 2) + 1) * accuracy);
      tmp->setPosX(tmp->getStartX());
      tmp->setPosY(tmp->getStartY());
      if (tmp->getPosX() != player.getPosX() && tmp->getPosY() != player.getPosY())
         mushs.push_back(tmp);
   }
}

void
Centipede::initCenti()
{
   CentipedeEntity *centi;

   centi = new CentipedeEntity(CENTIPEDE_LENGTH);
   centi->initPos(accuracy);
   centis.push_back(centi);
}

void
Centipede::init_game()
{
   score.load("scores/Centipede.score", 10);

   if (!init)
   {
      lifes = 2;
      mushs.clear();
      centis.clear();
      score.reset();
      map.loadMap("Maps/04.map");
      if (timeEnable)
         timerMoving.startTime();
      initPlayer();
      initMushs();
      initCenti();
      init = true;
   }
}

int
Centipede::checkCollisionMushs(int y, int x, const std::vector<ACharacter *> &mushs) const
{
   for (std::vector<ACharacter *>::const_iterator it = mushs.begin(); it != mushs.end(); ++it)
   {
      if ((*it)->getPosY() == y && (*it)->getPosX() == x)
         return (0);
   }
   return (1);
}

int
Centipede::checkCollisionPlayer()
{
   std::vector<CentipedeBody *> body;

   for (std::vector<CentipedeEntity *>::iterator it = centis.begin(); it != centis.end(); ++it)
      {
         body = (*it)->getBody();
         for (std::vector<CentipedeBody *>::iterator it2 = body.begin(); it2 != body.end(); ++it2)
         {
            if ((*it2)->getPosX() == player.getPosX() && (*it2)->getPosY() == player.getPosY())
               return (1);
         }
      }
   return (0);
}

void
Centipede::gereKey(InputButton::id_button button)
{
   if (button == InputButton::UP && player.getPosY() - accuracy >= map.getHeight() * accuracy - map.getHeight() / 4 * accuracy && checkCollisionMushs(player.getPosY() - accuracy, player.getPosX(), mushs))
      player.setPosY(player.getPosY() - accuracy);
   else if (button == InputButton::DOWN && player.getPosY() < map.getHeight() * accuracy - 2 * accuracy && checkCollisionMushs(player.getPosY() + accuracy, player.getPosX(), mushs))
      player.setPosY(player.getPosY() + accuracy);
   else if (button == InputButton::LEFT && player.getPosX() > accuracy && checkCollisionMushs(player.getPosY(), player.getPosX() - accuracy, mushs))
      player.setPosX(player.getPosX() - accuracy);
   else if (button == InputButton::RIGHT && player.getPosX() + accuracy < (map.getWidth() - 1) * accuracy && checkCollisionMushs(player.getPosY(), player.getPosX() + accuracy, mushs))
      player.setPosX(player.getPosX() + accuracy);
   else if (button == InputButton::SPACE && !shoot)
      shoot = player.createShoot(accuracy);
}

void
Centipede::reInitGame(bool fullgame)
{
   player.setPosY(player.getStartY());
   player.setPosX(player.getStartX());
   centis.clear();
   initCenti();
   if (fullgame)
      {
         lifes = 2;
         mushs.clear();
         initMushs();
         score.reset();
      }
}

bool
Centipede::playGame(const std::string &playerName)
{
   bool canDisplay;
  //  sounds.clear();
   //
  //  sounds.push_back("centipede");
   canDisplay = false;
   if (!timerMoving.isPaused() && timerMoving.getTimeElapsed() > 100000 || !timeEnable)
   {
      canDisplay = true;
      checkCollisionShoot();
      moveShoot();
      moveCentis();
      if (centis.empty())
         initCenti();
      if (checkCollisionPlayer())
      {
         if (--lifes <= 0)
         {
            score.save("scores/Centipede.score", playerName);
            reInitGame(true);
         }
         else
         {
            sleep(1);
            reInitGame(false);
         }
      }
      timerMoving.resetTime();

   }
   return (canDisplay);
}

void
Centipede::pause()
{
   timerMoving.paused(!timerMoving.isPaused());
}

void
Centipede::loadTextures(IDynLib *lib)
{
   lib->addSprite("BlueShip", "Sprites/centipede.png", 4 * 128, 0);
   lib->addSprite("CentiHead", "Sprites/centipede.png", 5 * 128, 0);
   lib->addSprite("CentiBody", "Sprites/centipede.png", 6 * 128, 0);
   lib->addSprite("Shoot", "Sprites/centipede.png", 7 * 128, 0);
   lib->addSprite("QMushroom", "Sprites/centipede.png", 3 * 128, 0);
   lib->addSprite("HMushroom", "Sprites/centipede.png", 2 * 128, 0);
   lib->addSprite("TMushroom", "Sprites/centipede.png", 128, 0);
   lib->addSprite("FMushroom", "Sprites/centipede.png", 0, 0);

   lib->setNameTextureMap("Sprites/chompermazetiles" + std::to_string(accuracy) + ".png");
   lib->setNameTextureLife("Sprites/heart.png");

   lib->addFont("text", "font/crackman.ttf");
   lib->addFont("score", "font/Square.ttf");

   lib->addSound("centipede", "sounds/nibbler_music.ogg");
}

int
Centipede::getLifes() const
{
   return (lifes);
}

const std::vector<std::string> & Centipede::getPosCharacters()
{
  posCharacters.clear();
  getCharacters();
  for (std::vector<ACharacter *>::iterator it = characters.begin() ; it != characters.end() ; ++it)
  {
    posCharacters.push_back(std::to_string((*it)->getPosX()) + " " + std::to_string((*it)->getPosY()) + " " + (*it)->getSprite());
  }
  return posCharacters;
}


const std::vector<ACharacter *> &
Centipede::getCharacters()
{
   characters.clear();
   std::vector<CentipedeBody *> body;

   characters.push_back(&player);
   for (std::vector<ACharacter *>::const_iterator it = mushs.begin(); it != mushs.end(); ++it)
      characters.push_back(*it);
   for (std::vector<CentipedeEntity *>::const_iterator it = centis.begin(); it != centis.end(); ++it)
      {
         body = (*it)->getBody();
         for (std::vector<CentipedeBody *>::const_iterator it2 = body.begin(); it2 != body.end(); ++it2)
            characters.push_back(*it2);
      }
   if (shoot)
      characters.push_back(shoot);
   return (characters);
}

void
Centipede::checkCollisionShoot()
{
   std::vector<CentipedeBody *> body;
   int pos;
   Mushroom *mushroom;

   if (shoot)
   {
      for (std::vector<ACharacter *>::iterator it = mushs.begin(); it != mushs.end(); ++it)
      {
         if ((*it)->getPosX() == shoot->getPosX() && (*it)->getPosY() == shoot->getPosY())
         {
            delete shoot;
            shoot = 0;
            if (dynamic_cast<Mushroom *>((*it))->decrLife() <= 0)
            {
               it = mushs.erase(it);
               score.add(1);
            }
            return ;
         }
      }
      CentipedeEntity *splited;
      for (std::vector<CentipedeEntity *>::iterator it = centis.begin(); it != centis.end(); ++it)
         {
            body = (*it)->getBody();
            pos = 0;
            for (std::vector<CentipedeBody *>::iterator it2 = body.begin(); it2 != body.end(); ++it2)
            {
               if ((*it2)->getPosX() == shoot->getPosX() && (*it2)->getPosY() == shoot->getPosY())
               {
                  delete shoot;
                  shoot = 0;
                  mushroom = new Mushroom();
                  mushroom->setPosX((*it2)->getPosX());
                  mushroom->setPosY((*it2)->getPosY());
                  mushs.push_back(mushroom);
                  if ((splited = (*it)->getSplited(pos, accuracy)))
                     centis.push_back(splited);
                  if (*it && (*it)->isEmpty())
                     centis.erase(it);
                  score.add(100);
                  return ;
               }
               ++pos;
            }
         }
      }
}

void
Centipede::moveShoot()
{
   if (shoot)
      {
         shoot->setPosY(shoot->getPosY() - accuracy);
         if (shoot->getPosY() < accuracy)
         {
            delete shoot;
            shoot = 0;
         }
      }
}

void
Centipede::moveCentis()
{
   for (std::vector<CentipedeEntity *>::iterator it = centis.begin(); it != centis.end(); ++it)
      (*it)->move(map, accuracy, mushs);
}

void
Centipede::setTimeEnable(bool time)
{
   timeEnable = time;
}

void
Centipede::get_map()
{
   int *mapret = map.getMap();
   int size = sizeof(arcade::GetMap) + (sizeof(uint16_t) * (map.getHeight() * map.getWidth()));
   int truesize = map.getHeight() * map.getWidth();
   std::vector<CentipedeBody *> body;
   uint16_t *mapp = new uint16_t[map.getHeight() * map.getWidth()];
   int i;

   i = -1;
   while (++i < truesize)
   {
      if (mapret[i] != 0 && mapret[i] != 45)
         mapp[i] = (uint16_t)arcade::TileType::BLOCK;
      else
         mapp[i] = (uint16_t)arcade::TileType::EMPTY;
   }
   for (std::vector<ACharacter *>::iterator it = mushs.begin(); it != mushs.end(); ++it)
   {
      if (*it)
         mapp[((*it)->getPosX() / 24) + (((*it)->getPosY() / 24) * map.getWidth())] = (int)arcade::TileType::BLOCK;
   }
   for (std::vector<CentipedeEntity *>::iterator it = centis.begin(); it != centis.end(); ++it)
      {
         if (*it)
         {
            body = (*it)->getBody();
            for (std::vector<CentipedeBody *>::iterator it2 = body.begin(); it2 != body.end(); ++it2)
            {
               if (*it2 && (*it2)->getPosY() >= 24)
                  mapp[((*it2)->getPosX() / 24) + (((*it2)->getPosY() / 24) * map.getWidth())] = (int)arcade::TileType::EVIL_DUDE;
            }
         }
      }
   if (shoot)
      mapp[(shoot->getPosX() / 24) + ((shoot->getPosY() / 24) * map.getWidth())] = (int)arcade::TileType::MY_SHOOT;
   arcade::GetMap *map2 = (arcade::GetMap *)malloc(size);
   map2->type = arcade::CommandType::GET_MAP;
   map2->width = map.getWidth();
   map2->height = map.getHeight();
   memcpy(&map2->tile[0], &mapp[0], sizeof(uint16_t) * (map.getWidth() * map.getHeight()));
   write(1, map2, size);
   free(map2);
   delete (mapp);
}

void
Centipede::setInit(bool state)
{
   init = state;
}

void getWhereAmI(Centipede *& game)
{
   arcade::WhereAmI *w;
   arcade::Position *p;

   w = (arcade::WhereAmI *)malloc(sizeof(arcade::WhereAmI) + sizeof(arcade::Position));
   w->type = arcade::CommandType::WHERE_AM_I;
   w->lenght = 1;
   p = (arcade::Position *)malloc(sizeof(arcade::Position));
   p->x = game->getCharacters()[0]->getPosX() / 24;
   p->y = game->getCharacters()[0]->getPosY() / 24;
   memcpy(&w->position[0], &p[0], sizeof(arcade::Position));
   write(1, w, sizeof(arcade::WhereAmI) + sizeof(arcade::Position));
   // free(w);
   // free(p);

}


extern "C"
{
  AGame * create_game()
  {
    return new Centipede();
  }

   void Play(void)
   {
      arcade::CommandType CommandType;
      Centipede *game = new Centipede();
      game->setTimeEnable(false);
      game->setAccuracy(24);
      game->init_game();
      while (42)
      {
         read(0, &CommandType, sizeof(arcade::CommandType));
         switch (CommandType)
         {
            case arcade::CommandType::WHERE_AM_I:
              getWhereAmI(game);
            break;
            case arcade::CommandType::GET_MAP:
              game->get_map();
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
            case arcade::CommandType::SHOOT:
            game->gereKey(InputButton::SPACE);
            break;
         }
      }
   }
}
