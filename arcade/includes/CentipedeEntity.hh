#ifndef CENTIPEDE_ENTITY_HH_
# define CENTIPEDE_ENTITY_HH_

# include <vector>
# include <algorithm>
# include "Map.hh"
# include "CentipedeBody.hh"
# include "ACharacter.hh"

class CentipedeEntity
{
public:
   CentipedeEntity(int);
   ~CentipedeEntity();
   std::vector<CentipedeBody *> getBody();
   void initPos(int);
   void moveTo(int, int);
   bool isEmpty() const;
   void move(Map const &map, int accuracy, std::vector<ACharacter *> const &);
   int checkMushs(int y, int x, const std::vector<ACharacter *> &mushs) const;
   int getPosY() const;
   int getPosX() const;
   CentipedeEntity *getSplited(int pos, int accuracy);
   InputButton::id_button getWay();
private:
   InputButton::id_button way;
   int getDirection(int, int, int, int);
   std::vector<CentipedeBody *> body;
protected:
   CentipedeEntity(int pos, std::vector<CentipedeBody *>, InputButton::id_button, int accuracy);
};

#endif
