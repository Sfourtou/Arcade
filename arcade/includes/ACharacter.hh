/*
** Character.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 18:05:30 2016 fourto_s
** Last update Sat Apr 02 00:12:49 2016 Sebastien Fourtou
*/

#ifndef CHARACTER_HH_
#define CHARACTER_HH_

#include <iostream>
#include <string>
#include "arcade.hh"

class ACharacter
{
protected:
  int posX;
  int posY;
  int startX;
  int startY;
  std::string name;
  InputButton::id_button button;
public:
  int getPosX() const;
  int getPosY() const;
  int getStartX() const;
  int getStartY() const;
  void setIdButton(InputButton::id_button);
  InputButton::id_button getIdButton() const;
  std::string getName() const;
  void setPosX(const int &);
  void setPosY(const int &);
  void setStartX(const int &);
  void setStartY(const int &);
  virtual std::string getSprite() const = 0;
public:
  ACharacter(const std::string &);
  virtual ~ACharacter();
};
#endif
