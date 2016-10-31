#ifndef CENTIPEDE_HH_
# define CENTIPEDE_HH_

# include <string.h>
# include <unistd.h>
# include "Utils.hh"
# include "AGame.hh"
# include "Timer.hh"
# include "Ship.hh"
# include "Mushroom.hh"
# include "Shoot.hh"
# include "CentipedeEntity.hh"
# include "CentipedeBody.hh"
# include "Protocol.hpp"

# define NOTHING 0
# define BLOCK_25 1
# define BLOCK_50 2
# define BLOCK_75 3
# define BLOCK_100 4
# define IS_BLOCK(x) (x > 0 && x < 5)
# define MAX_POS_Y 15
# define CENTIPEDE_LENGTH 10

class Centipede : public AGame
{
public:
   Centipede();
   virtual ~Centipede();
   virtual void init_game();
   virtual void gereKey(InputButton::id_button);
   virtual bool playGame(const std::string &playName);
   virtual void pause();
   virtual void loadTextures(IDynLib *);
   virtual int  getLifes() const;
   virtual const std::vector<std::string> & getPosCharacters();
   virtual const std::vector<ACharacter *> &getCharacters();
   void reInitGame(bool);
   // init player
   void initPlayer();
   // init vector of mushs
   void initMushs();
   // init vector of centi
   void initCenti();
   int checkCollisionMushs(int y, int x, const std::vector<ACharacter *> &mushs) const;
   void moveShoot();
   void moveCentis();
   void checkCollisionShoot();
   // return 1 if collision
   int checkCollisionPlayer();
   void setTimeEnable(bool);
   void get_map();
   void setInit(bool);
private:
   std::vector<ACharacter *> mushs;
   std::vector<CentipedeEntity *> centis;
   Shoot *shoot;
   Ship player;
   Timer timerMoving;
   bool init;
   int lifes;
   bool timeEnable;
};

#endif
