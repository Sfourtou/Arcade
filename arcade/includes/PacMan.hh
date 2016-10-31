/*
** PacMan.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 23:34:09 2016 fourto_s
** Last update Sun Apr 03 08:53:16 2016 Sebastien Fourtou
*/

#ifndef PACMAN_HH_
#define PACMAN_HH_

#include "PacmanEntity.hh"
#include "Ghost.hh"
#include "AGame.hh"

class PacMan : public AGame
{
public:
  PacMan();
  virtual ~PacMan();
private:
  PacmanEntity pacman;
  Ghost     marron;
  Ghost     blue;
  Ghost     red;
  Ghost     pink;
  Timer     timer_moving;
  Timer     timer_animated;
  Timer     timer_state;
  Timer     timer_ghost;
  Timer     timer_chase;
  Timer     timer_frightened;
  bool      init;
  bool      time_enabled;
private:
  bool gere_collision_x(int);
  bool gere_collision_y(int);
  void move();
  void initGhosts();
  void initPacmanEntity();
  void changeGhostBehavior(int &, int &);
  bool noMorePacGum();
  void changeStateCharacters();
  void GhostNoMoreFrightened();
  void calcPosGhosts();
  void reLaunchGame();
  bool hasEatGhost(std::vector<Ghost *>);
  void setInit(bool);
public:
  virtual void loadTextures(IDynLib *);
  virtual void gereKey(InputButton::id_button);
  virtual void init_game();
  virtual bool playGame(const std::string & playerName);
  virtual void pause();
  virtual void manageScore();
  virtual int getLifes() const;
  virtual const std::vector<ACharacter *> & getCharacters();
  virtual const std::vector<std::string> & getPosCharacters();
  void setTimeEnabled(bool);
  void setSpeedCharacters(int speed);
};

#define SPEED 2
#define TIME_EATING 8
#define TIME_PAC_GUM 18
#define START_CASE 45 // Depart pacman
#define BIG_PAC_GUM_LIGHT 29 // La grosse boule eclairee
#define BIG_PAC_GUM 28 // La grosse boule pas eclairee
#define NORMAL_PAC_GUM 30 // La petite  boule
#define TP_LEFT 98 // Passage de tp a gauche
#define TP_RIGHT 99 // Passage de tp a droite
#define NOTHING 0 // Rien
// walls : 4 - 9 - 6 - 17 - 24 - 26 || < 28 && > 0
#define NORMAL_SCORE 10
#define BIG_SCORE 50
#define STOP 9999
#define START_RED 46
#define START_ORANGE 47
#define START_BLUE 48
#define START_MARRON 49

#endif
