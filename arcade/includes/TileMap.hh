/*
** TileMap.hh for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/includes
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 16:02:52 2016 fourto_s
** Last update Sun Apr 03 05:13:47 2016 Sebastien Fourtou
*/

#ifndef TILEMAP_HH_
#define TILEMAP_HH_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hh"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
  bool load(int *, int, int, const std::string & text, int);
private:
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};

#endif
