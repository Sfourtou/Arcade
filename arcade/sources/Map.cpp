/*
** Map.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 12:41:31 2016 fourto_s
** Last update Sat Apr 02 20:27:47 2016 Sebastien Fourtou
*/

#include <stdlib.h>
#include "Utils.hh"
#include "Map.hh"

Map::Map()
{
}

Map::~Map()
{

}

void Map::fill_map(std::vector<std::string> strings)
{
  bool test = false;
  int  y = 0;
  _map = new int[height * strings[0].size()];
  for (std::vector<std::string>::iterator it = strings.begin() ; it != strings.end() ; ++it){
    int j = 0;
    while ((*it)[j])
    {
      std::string buffer;
      while ((*it)[j] && (*it)[j] != ',')
      {
        buffer.push_back((*it)[j]);
        ++j;
      }
      if (Utils::isNumber(buffer.c_str()))
      {
        _map[y] = atoi(buffer.c_str());
        ++y;
      }
      else
      {
        return;//EXCEPTION Invalid Map
      }
      ++j;
    }
    if (!test)
    {
      width = y;
      test = true;
    }
  }
}

int Map::loadMap(const std::string & name)
{
  std::ifstream afile(name.c_str(), std::ios::in);

  if (afile.is_open())
  {
    std::string buffer;
    std::vector<std::string> strings;
    while (getline(afile, buffer))
    {
      buffer.push_back('\0');
      strings.push_back(buffer);
    }
    height = strings.size();
    fill_map(strings);
    afile.close();
  }
  else {
    std::cout << "Unable to load Map " << name << std::endl;
    //EXCEPTION
  }
  return (0);
}

int Map::getWidth() const
{
  return width;
}

int Map::getHeight() const
{
  return height;
}

int * Map::getMap() const
{
  return _map;
}

int * Map::copyMap()
{
  int * new_map = new int[getWidth() * getHeight()];

  for (int i = 0; i < getWidth() * getHeight() ; ++i){
    new_map[i] = _map[i];
  }
  return new_map;
}
