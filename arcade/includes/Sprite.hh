/*
** Sprite.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 14:24:25 2016 fourto_s
** Last update Sun Apr 03 05:15:30 2016 Sebastien Fourtou
*/

#ifndef SPRITE_HH_
#define SPRITE_HH_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Sprite
{
public:
  Sprite();
  ~Sprite();
public:
  void addSprite(const std::string & type, const std::string & text, int x, int y, int);
  sf::Sprite * getSprite(const std::string & name);
  void addTexture(sf::Texture *);
private:
  std::map<std::string, sf::Sprite *> _sprites;
  std::vector<sf::Texture *> _textures;
};

#endif
