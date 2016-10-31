/*
** Game.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 23:16:24 2016 fourto_s
** Last update Sun Apr 03 09:10:22 2016 Sebastien Fourtou
*/

#ifndef AGAME_HH_
# define AGAME_HH_

#include <cstdlib>
#include <string>
#include <vector>
#include "IDynLib.hh"
#include "Score.hh"
#include "ACharacter.hh"

class AGame
{
public:
  AGame(const std::string & name);
  virtual ~AGame();
protected:
  std::string name;
  Map map;
  Score score;
  int accuracy;
  std::vector<ACharacter *> characters;
  std::vector<std::string> posCharacters;
  std::vector<std::string> sounds;
public:
  virtual void init_game() = 0;
  virtual void gereKey(InputButton::id_button) = 0;
  virtual bool playGame(const std::string & playerName) = 0;
  virtual void pause() = 0;
  virtual void loadTextures(IDynLib *) = 0;
  virtual int getLifes() const = 0;
  virtual const std::vector<ACharacter *> & getCharacters() = 0;
  virtual const std::vector<std::string> & getPosCharacters() = 0;
  int getScore() const;
  int getMapWidth() const;
  int getMapHeight() const;
  std::vector<std::string> getHighScores() const;
  int * getMapi() const;
  const Map & getMap() const;
  void setAccuracy(int);
  const std::string & getName() const;
  std::vector<std::string> getTypesSound() const;
  virtual void setInit(bool) = 0;
};

#endif
