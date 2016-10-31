#ifndef CORE_HH_
# define CORE_HH_

#include <vector>
#include "arcade.hh"
#include "IDynLib.hh"
#include "AGame.hh"

class Core
{
public:
  Core();
  ~Core();
private:
  std::vector<AGame *> games;
  std::vector<IDynLib *> libs;
  int idxGame;
  int idxLib;
public:
  void addGame(AGame *);
  void addLib(IDynLib *);
  int playGame(const std::string & );
  void displayCharacters(std::vector<std::string>);
  void displayGame();
  void changeLib(int);
  void changeGame(int);
  void setIdxGame(int idx);
  void setIdxLib(int idx);
  void playSounds();
};

#define TILESIZE 24

#endif
