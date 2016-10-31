/*
** Map.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 12:40:38 2016 fourto_s
** Last update Sat Apr 02 20:23:51 2016 Sebastien Fourtou
*/

#ifndef MAP_HH_
#define MAP_HH_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Map
{
private:
  int * _map;
  int width;
  int height;
public:
  Map();
  ~Map();
  int loadMap(const std::string & name);
  void fill_map(std::vector<std::string> strings);
  int getHeight() const;
  int getWidth() const;
  int * getMap() const;
  int * copyMap();

};

#endif
