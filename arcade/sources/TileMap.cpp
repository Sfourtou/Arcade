/*
** TileMap.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 16:05:21 2016 fourto_s
** Last update Sun Apr 03 05:13:30 2016 Sebastien Fourtou
*/

#include "TileMap.hh"
#include "Sfml.hh"

bool TileMap::load(int * map, int width, int height, const std::string & text, int tilesize)
{
  sf::Vector2u tileSize(tilesize, tilesize);

  if (!m_tileset.loadFromFile(text))
    return false;

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(width * height * 4);

  for (int i = 0 ; i < width ; ++i)
  {
    for (int j = 0; j < height ; ++j)
      {
        int tileNumber = map[i + j * width] - 1;
        if (tileNumber == 44)
          tileNumber = -1;
        int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
        int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
        sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
        quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
        quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
        quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }
  return true;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *=getTransform();
  states.texture = &m_tileset;
  target.draw(m_vertices, states);
}
