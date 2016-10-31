#ifndef NIBBLER_HH_
#define NIBBLER_HH_

#include <unistd.h>
#include "SnakeEntity.hh"
#include "Fruit.hh"
#include "Timer.hh"
#include "AGame.hh"

class Nibbler : public AGame
{
  public:
    Nibbler();
    virtual ~Nibbler();
    virtual void init_game();
    virtual void gereKey(InputButton::id_button);
    virtual bool playGame(const std::string &);
    virtual void pause();
    virtual void loadTextures(IDynLib *);
    virtual const std::vector<ACharacter *> & getCharacters();
    virtual const std::vector<std::string> & getPosCharacters();

    void setTimeEnable(bool);
    virtual int getLifes() const;

  private:
    void initSnakeEntity();
    void move();
    bool gere_collision_x(int col);
    bool gere_collision_y(int col);
    void fruitPop();
    void checkFruit();
    void setInit(bool);
  private:
    Timer       timerMoving;
    SnakeEntity snake;
    bool        init;
    bool        hasCollision;
    InputButton::id_button button;
    Fruit apple;
    bool timeEnable;
};

#endif
