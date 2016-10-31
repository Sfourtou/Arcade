/*
** ACharacter.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 18:07:55 2016 fourto_s
** Last update Sat Mar 19 03:36:09 2016 fourto_s
*/

#include "ACharacter.hh"

ACharacter::ACharacter(const std::string & name) :
  name(name), button(InputButton::UNDEF)
{
}

ACharacter::~ACharacter()
{
}

int ACharacter::getPosX() const
{
  return posX;
}

int ACharacter::getPosY() const
{
  return posY;
}

int ACharacter::getStartX() const
{
  return startX;
}

int ACharacter::getStartY() const
{
  return startY;
}

InputButton::id_button ACharacter::getIdButton() const
{
  return button;
}

void ACharacter::setIdButton(InputButton::id_button new_button)
{
  button = new_button;
}

void ACharacter::setPosX(const int & pos)
{
  posX = pos;
}

void ACharacter::setPosY(const int & pos)
{
  posY = pos;
}

void ACharacter::setStartX(const int & pos)
{
  startX = pos;
}

void ACharacter::setStartY(const int & pos)
{
  startY = pos;
}

std::string ACharacter::getName() const
{
  return name;
}
