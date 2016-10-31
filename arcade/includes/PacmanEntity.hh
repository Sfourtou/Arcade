/*
** PacmanEntity.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 18:16:26 2016 fourto_s
** Last update Sat Apr 02 23:47:32 2016 Sebastien Fourtou
*/

#ifndef PACMANENTITY_HH_
#define PACMANENTITY_HH_

#include "ACharacter.hh"
#include "Map.hh"

class Ghost;

class PacmanEntity : public ACharacter
{
public:
  PacmanEntity();
  ~PacmanEntity();
private:
  bool state;
  size_t lifes;
  InputButton::id_button way;
  int speed;
public:
  bool    getState() const;
  void    setState(bool);
  size_t  getLifes() const;
  void    setLifes(size_t new_lifes);
  InputButton::id_button getWay() const;
  void setWay(InputButton::id_button);
  virtual std::string getSprite() const;
  bool touchedGhost(std::vector<Ghost *> &, int);
  void setSpeed(int);
};

#endif
