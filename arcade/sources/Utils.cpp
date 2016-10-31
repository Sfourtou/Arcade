/*
** utils.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 12:56:46 2016 fourto_s
** Last update Sat Apr 02 20:21:32 2016 Sebastien Fourtou
*/

#include "Utils.hh"

bool Utils::isNumber(const char *str)
{
  int i = -1;

  while (str[++i])
  {
    if (str[i] >= '0' && str[i] <= '9')
      i = i;
    else
      return false;
  }
  return true;
}

int Utils::getStartX(Map & map, int nb, int tileSize)
{
  for (int y = 0 ; y < map.getHeight() ; ++y){
    for (int x = 0 ; x < map.getWidth() ; ++x)
    {
      if (map.getMap()[x + y * map.getWidth()] == nb)
        return (x * tileSize);
    }
  }
  return (-1);
}

int Utils::getStartY(Map & map, int nb, int tileSize)
{
  for (int y = 0 ; y < map.getHeight() ; ++y){
    for (int x = 0 ; x < map.getWidth() ; ++x)
    {
      if (map.getMap()[x + y * map.getWidth()] == nb)
        return (y * tileSize);
    }
  }
  return (-1);
}

bool Utils::isPacgum(int nb)
{
  if (nb == BIG_PAC_GUM_LIGHT || nb == BIG_PAC_GUM || nb == NORMAL_PAC_GUM)
    return true;
  return false;
}
