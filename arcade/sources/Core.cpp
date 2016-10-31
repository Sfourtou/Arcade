 #include "Core.hh"

Core::Core() :
  idxGame(0), idxLib(0)
{
}

Core::~Core()
{
}

void Core::addGame(AGame * game)
{
  games.push_back(game);
}

void Core::addLib(IDynLib * lib)
{
  libs.push_back(lib);
}

void Core::displayCharacters(std::vector<std::string> characters)
{
  for (std::vector<std::string>::iterator it = characters.begin() ; it != characters.end() ; ++it)
  {
    std::stringstream s;
    int x;
    int y;
    std::string sprite;

    s << *it;
    s >> x >> y >> sprite;
    libs[idxLib]->drawCharacter(x, y, sprite);
  }
}

void Core::playSounds()
{
  std::vector<std::string> types = games[idxGame]->getTypesSound();

  for (std::vector<std::string>::iterator it = types.begin() ; it != types.end() ; ++it)
  {
    libs[idxLib]->playSound(*it);
  }
}

void Core::displayGame()
{
  std::vector<std::string> characters = games[idxGame]->getPosCharacters();

  libs[idxLib]->clearScreen();
  libs[idxLib]->drawMap(games[idxGame]->getMapi(), games[idxGame]->getMapWidth(), games[idxGame]->getMapHeight());
  libs[idxLib]->drawHighScore(games[idxGame]->getHighScores(), false);
  libs[idxLib]->drawScore(games[idxGame]->getScore());
  libs[idxLib]->drawText(games[idxGame]->getName(), 50);
  libs[idxLib]->drawLifes(games[idxGame]->getLifes());
  displayCharacters(characters);
  libs[idxLib]->display();

}

void Core::changeLib(int op)
{
  if (libs.size() == 1)
      return;
  libs[idxLib]->close();
  if (idxLib + op < 0)
   idxLib = libs.size() - 1;
  else if(idxLib + op >= libs.size())
      idxLib = 0;
  else
      idxLib += op;
  libs[idxLib]->setTileSize(TILESIZE);
  libs[idxLib]->createWindows();
  if (libs[idxLib]->needSprites())
    games[idxGame]->loadTextures(libs[idxLib]);
  games[idxGame]->setAccuracy(libs[idxLib]->getTileSize());
}

void Core::changeGame(int op)
{
  libs[idxLib]->leave();
  if (games.size() == 1)
    return;
//  games[idxGame]->pause();
if (idxGame + op < 0)
idxGame = games.size() - 1;
  else if(idxGame + op >= games.size())
    idxGame = 0;
  else
    idxGame += op;
  games[idxGame]->setAccuracy(libs[idxLib]->getTileSize());
  if (libs[idxLib]->needSprites())
    games[idxGame]->loadTextures(libs[idxLib]);
  games[idxGame]->init_game();
}

int Core::playGame(const std::string & playerName)
{
  InputButton::id_button pressedButton;

  libs[idxLib]->setTileSize(TILESIZE);
  games[idxGame]->setAccuracy(libs[idxLib]->getTileSize());
  libs[idxLib]->createWindows();
  games[idxGame]->init_game();
  if (libs[idxLib]->needSprites())
    games[idxGame]->loadTextures(libs[idxLib]);

  while (libs[idxLib]->WindowIsOpen())
    {
      pressedButton = libs[idxLib]->getInput();
      if (pressedButton == InputButton::ECHAP)
        return (0);
      if (pressedButton == InputButton::TWO)
      {
         changeLib(-1);
         pressedButton = InputButton::UNDEF;
      }
      if (pressedButton == InputButton::THREE)
      {
         changeLib(1);
         pressedButton = InputButton::UNDEF;
      }
        if (pressedButton == InputButton::FOUR)
        {
           changeGame(-1);
           pressedButton = InputButton::UNDEF;
           continue ;
        }
        if (pressedButton == InputButton::FIVE)
        {
           changeGame(1);
           pressedButton = InputButton::UNDEF;
           continue ;
        }
        if (pressedButton == InputButton::EIGHT)
       {
          libs[idxLib]->leave();
          games[idxGame]->setInit(false);
          games[idxGame]->init_game();
          pressedButton = InputButton::UNDEF;
       }
       if (pressedButton == InputButton::NINE)
       {
          libs[idxLib]->leave();
          libs[idxLib]->close();
          pressedButton = InputButton::UNDEF;
          return (1);
       }
      games[idxGame]->gereKey(pressedButton);
      if ((games[idxGame]->playGame(playerName)))
      {
        playSounds();
        displayGame();
      }
    }
    return (1);
}

void
Core::setIdxLib(int idx)
{
   idxLib = idx;
}

void
Core::setIdxGame(int idx)
{
   idxGame = idx;
}
