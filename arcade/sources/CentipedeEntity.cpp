#include "CentipedeEntity.hh"

CentipedeEntity::CentipedeEntity(int parts)
   : way(InputButton::RIGHT)
{
   for (int i = 0; i < parts; ++i)
   {
      if (i == 0)
         body.push_back(new CentipedeBody("CentiHead"));
      else
         body.push_back(new CentipedeBody());
   }
}

CentipedeEntity::~CentipedeEntity()
{
}

int
CentipedeEntity::getDirection(int, int, int, int)
{
   return (1);
}

std::vector<CentipedeBody *>
CentipedeEntity::getBody()
{
   return (body);
}

void
CentipedeEntity::initPos(int accuracy)
{
   int y;
   int x;

   y = accuracy;
   x = accuracy;
   for (std::vector<CentipedeBody *>::iterator it = body.begin(); it != body.end(); ++it)
   {
      (*it)->setPosY(y--);
      (*it)->setPosX(x);
   }
}

void
CentipedeEntity::moveTo(int y, int x)
{
   CentipedeBody *head = body[0];
   int oldy;
   int oldx;
   int tmpy;
   int tmpx;

   oldy = head->getPosY();
   oldx = head->getPosX();
   head->setPosX(x);
   head->setPosY(y);
   for (std::vector<CentipedeBody *>::iterator it = body.begin() + 1; it != body.end(); ++it)
      {
         tmpy = (*it)->getPosY();
         tmpx = (*it)->getPosX();
         (*it)->setPosX(oldx);
         (*it)->setPosY(oldy);
         oldx = tmpx;
         oldy = tmpy;
      }
}

int
CentipedeEntity::checkMushs(int y, int x, const std::vector<ACharacter *> &mushs) const
{
   for (std::vector<ACharacter *>::const_iterator it = mushs.begin(); it != mushs.end(); ++it)
      {
         if ((*it)->getPosX() == x && (*it)->getPosY() == y)
            return (0);
      }
   return (1);
}

void
CentipedeEntity::move(Map const &map, int accuracy, const std::vector<ACharacter *> &mushs)
{
   CentipedeBody *head = body[0];

   if (way == InputButton::RIGHT)
   {
      if (head->getPosX() < map.getWidth() * accuracy - 2 * accuracy && checkMushs(head->getPosY(), head->getPosX() + accuracy, mushs))
         moveTo(head->getPosY(), head->getPosX() + accuracy);
      else if (head->getPosY() + accuracy < (map.getHeight() - 1) * accuracy && checkMushs(head->getPosY() + accuracy, head->getPosX(), mushs))
         {
            moveTo(head->getPosY() + accuracy, head->getPosX());
            way = InputButton::LEFT;
         }
      else
         {
            moveTo(head->getPosY() - accuracy, head->getPosX());
            way = InputButton::LEFT;
         }
      }
   else if (way == InputButton::LEFT)
   {
      if (head->getPosX() - accuracy > 0  && checkMushs(head->getPosY(), head->getPosX() - accuracy, mushs))
         moveTo(head->getPosY(), head->getPosX() - accuracy);
      else if (head->getPosY() + accuracy < (map.getHeight() - 1) * accuracy && checkMushs(head->getPosY() + accuracy, head->getPosX(), mushs))
         {
            moveTo(head->getPosY() + accuracy, head->getPosX());
            way = InputButton::RIGHT;
         }
         else
            {
               moveTo(head->getPosY() - accuracy, head->getPosX());
               way = InputButton::LEFT;
            }
   }
}

int
CentipedeEntity::getPosX() const
{
   return (body[0]->getPosX());
}

int
CentipedeEntity::getPosY() const
{
   return (body[0]->getPosY());
}

InputButton::id_button
CentipedeEntity::getWay()
{
   return (way);
}

CentipedeEntity *
CentipedeEntity::getSplited(int pos, int accuracy)
{
   InputButton::id_button nway;
   std::vector<CentipedeBody *> nlist;

   if (way == InputButton::LEFT)
      nway = InputButton::RIGHT;
   else if (way == InputButton::RIGHT)
      nway = InputButton::LEFT;
   else if (way == InputButton::UP)
      nway = InputButton::DOWN;
   else if (way == InputButton::DOWN)
      nway = InputButton::UP;
   if (body.begin() + pos + 1 < body.end() && pos != 0)
   {
      CentipedeEntity *ncenti = new CentipedeEntity(pos, body, nway, accuracy);
      body.erase(body.begin() + pos, body.end());
      return (ncenti);
   }
   body.erase(body.end() - 1);
   return (0);
}

CentipedeEntity::CentipedeEntity(int pos, std::vector<CentipedeBody *> pbody, InputButton::id_button nway, int accuracy)
{
   CentipedeBody *tmp;
   bool isFirst;

   isFirst = true;
   for (std::vector<CentipedeBody *>::iterator it = pbody.begin(); it != pbody.end(); ++it)
   {
      if (pos == 0)
      {
         if (!isFirst)
            tmp = new CentipedeBody();
         else
            tmp = new CentipedeBody("CentiHead");
         isFirst = false;
         tmp->setPosX((*it)->getPosX());
         tmp->setPosY((*it)->getPosY() + accuracy);
         body.push_back(tmp);
      }
      else
         --pos;
   }
   way = nway;
}

bool
CentipedeEntity::isEmpty() const
{
   return (body.empty());
}
