/*
** AGame.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 23:27:50 2016 fourto_s
** Last update Sun Apr 03 09:10:13 2016 Sebastien Fourtou
*/

#include "AGame.hh"

AGame::AGame(const std::string & name) :
  name(name), accuracy(0)
{
}

AGame::~AGame()
{
}

int * AGame::getMapi() const
{
  return map.getMap();
}

const Map & AGame::getMap() const
{
  return map;
}

int AGame::getMapWidth() const
{
  return map.getWidth();
}

int AGame::getMapHeight() const
{
  return map.getHeight();
}

void AGame::setAccuracy(int new_accuracy)
{
  accuracy = new_accuracy;
}

std::vector<std::string> AGame::getHighScores() const
{
  return (score.getHighScores());
}

int AGame::getScore() const
{
  return (score.getScore());
}

const std::string & AGame::getName() const
{
  return name;
}

std::vector<std::string> AGame::getTypesSound() const
{
  return sounds;
}
