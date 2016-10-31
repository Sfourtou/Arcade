/*
** Utils.hpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Tue Mar 15 13:09:14 2016 fourto_s
** Last update Sat Apr 02 15:51:25 2016 Sebastien Fourtou
*/

#ifndef UTILS_HH__
#define UTILS_HH__

#include "Map.hh"
#include "PacMan.hh"

class Utils
{
public:
  static bool isNumber(const char * str);
  static int  getStartX(Map & map, int nb, int);
  static int  getStartY(Map & map, int nb, int);
  static bool isPacgum(int);
};

#endif
