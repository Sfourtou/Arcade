/*
** Sprite.cpp for cpp_arcade in /home/fourto_s/Projets/Tek_2/cpp_arcade/fourto_s/sources
**
** Made by fourto_s
** Login   <fourto_s@epitech.net>
**
** Started on  Mon Mar 14 14:22:44 2016 fourto_s
** Last update Sun Apr 03 05:15:07 2016 Sebastien Fourtou
*/

#include "Sprite.hh"
#include "Sfml.hh"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::addSprite(const std::string & type, const std::string & text, int x, int y, int tilesize)
{
  sf::Texture * texture = new sf::Texture();
  sf::Sprite * sprite = new sf::Sprite();

  if (!texture->loadFromFile(text))
    {
      std::cout << "Unable to load texture " << text << std::endl;
      return;
    }

  _textures.push_back(texture);
  sprite->setTexture(*texture);
  sprite->setTextureRect(sf::IntRect(x, y, 128, 128));
  sprite->setScale(sf::Vector2f((double)tilesize / (double)128, (double)tilesize / (double)128));
  _sprites[type] = sprite;
}

sf::Sprite * Sprite::getSprite(const std::string & name)
{
  if (_sprites.find(name) == _sprites.end())
    std::cerr << "ERROR CAN NOT FIND SPRITE" << std::endl;
  return _sprites[name];
}

void Sprite::addTexture(sf::Texture * text)
{
  _textures.push_back(text);
}
