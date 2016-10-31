/*
** Ghost.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Fri Mar 18 17:33:09 2016 fourto_s
** Last update Sat Apr 02 23:50:34 2016 Sebastien Fourtou
*/

#ifndef GHOST_HH_
#define GHOST_HH_

#include "Map.hh"
#include "ACharacter.hh"
#include "PacmanEntity.hh"
#include "Timer.hh"

class Ghost : public ACharacter
{
public:
  Ghost(const std::string &);
  ~Ghost();
private:
  bool state;
  bool frightened;
  bool search;
  bool changeDir;
  bool inBox;
  bool state_frightened;
  bool hasBeenEat;
  bool eat;
  InputButton::id_button my_button;
  int speed;
public:
  bool isWalkable(int);
  bool isFrightened();
  void move(Map &, InputButton::id_button, int);
  void find_next_move(Map &, int , int , int);
  void setState(bool new_state);
  bool getState() const;
  bool gere_collision_x(Map &, int, int);
  bool gere_collision_y(Map &, int, int);
  void goal_red(Map &, const PacmanEntity &, int);
  void goal_pink(Map &, const PacmanEntity &, int, InputButton::id_button);
  void goal_blue(const PacmanEntity &, const Ghost &, Map & map, int);
  void goal_marron(const PacmanEntity &, Map &, int);
  void setSearch(bool);
  void setFrightened(bool);
  void randomMove(Map &, int);
  void setHasBeenEat(bool);
  bool isEaten() const;
  void setStateFrightened(bool);
  bool getStateFrightened() const;
  void setInBox(bool);
  std::string getSprite() const;
  InputButton::id_button getWay() const;
  Timer * getTimer() const;
  bool beingEat() const;
  void setBeingEat(bool);
  void setSpeed(int speed);
};


#endif
