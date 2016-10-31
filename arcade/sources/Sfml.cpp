
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Protocol.hpp"

#include "Sfml.hh"
#include "Map.hh"
#include "TileMap.hh"

Sfml::Sfml() :
  tilesize(24), name("")
{
  buttons[sf::Keyboard::Up] = InputButton::UP;
  buttons[sf::Keyboard::Down] = InputButton::DOWN;
  buttons[sf::Keyboard::Right] = InputButton::RIGHT;
  buttons[sf::Keyboard::Left] = InputButton::LEFT;
  buttons[sf::Keyboard::Escape] = InputButton::ECHAP;
  buttons[sf::Keyboard::Space] = InputButton::SPACE;
  buttons[sf::Keyboard::Return] = InputButton::ENTER;
  buttons[sf::Keyboard::Num2] = InputButton::TWO;
  buttons[sf::Keyboard::Num3] = InputButton::THREE;
  buttons[sf::Keyboard::Num4] = InputButton::FOUR;
  buttons[sf::Keyboard::Num5] = InputButton::FIVE;
  buttons[sf::Keyboard::Num8] = InputButton::EIGHT;
  buttons[sf::Keyboard::Num9] = InputButton::NINE;
  lastButtonPressed = InputButton::UNDEF;
}

void Sfml::setTileSize(int size)
{
  tilesize = size;
}

void Sfml::addSound(const std::string & type, const std::string & file)
{
  sf::Music * buffer = new sf::Music();

  if (!buffer->openFromFile(file))
  {
    std::cout << "Unable to load sound from file " << file << std::endl;
    return ;
  }
  sounds[type] = buffer;
}

void Sfml::playSound(const std::string & type)
{
  if (sounds[type]->getStatus() != sf::SoundSource::Playing)
  {
    if (sounds.find("pacman") != sounds.end())
      sounds["pacman"]->stop();
    else if (sounds.find("nibbler") != sounds.end())
      sounds["nibbler"]->stop();
    else if (sounds.find("centipede") != sounds.end())
      sounds["centipede"]->stop();
    sounds[type]->play();
  }
}

void Sfml::addFont(const std::string & type, const std::string & font)
{
  sf::Font MyFont;

  if (!MyFont.loadFromFile(font))
  {
    std::cout << "Unable to load font " << font << std::endl;
    return;
  }

  fonts[type] = MyFont;
}

void Sfml::addSprite(const std::string & name, const std::string & text, int x, int y)
{
  sprite.addSprite(name, text, x, y, tilesize);
}

void Sfml::setNameTextureLife(const std::string & name)
{
  textureLife = name;
}

void Sfml::setNameTextureMap(const std::string & name)
{
  textureMap = name;
}

void Sfml::createWindows()
{
  sf::ContextSettings settings;

  settings.antialiasingLevel = 8;
  window.create(sf::VideoMode(WINX, WINY), "Arcades");
  window.setFramerateLimit(60);
  window.clear();
  window.display();
}

bool		Sfml::WindowIsOpen()
{
  return window.isOpen();
}

void Sfml::drawMap(int * map, int widt, int heigh)
{
  TileMap tile;

  width = widt;
  height = heigh;
  tile.load(map, widt, heigh, textureMap, tilesize);
  window.draw(tile);
}

void Sfml::drawScore(int score)
{
  std::stringstream s;
  s << score;
  sf::Text Text(s.str(), fonts["score"], 30);

  Text.setPosition(tilesize / 2, tilesize * (height + 1));
  window.draw(Text);
}

void Sfml::drawText(const std::string & texte, int size)
{
  sf::Text Text(texte.c_str(), fonts["text"], size);

  Text.setColor(sf::Color(255, 242, 0));
  Text.setPosition((width * tilesize) + (((WINX - width * tilesize) / 2) - (Text.getLocalBounds().width / 2)), tilesize);
  window.draw(Text);
}

void Sfml::drawLifes(int lifes)
{
  int x = tilesize * (width - 3);
  int y = tilesize * (height + 1);

  sf::Sprite my_sprite;
  sf::Texture * text = new sf::Texture();
  if (textureLife == "")
    return;
  if (!text->loadFromFile(textureLife))
  {
    std::cout << "Unable to load texture " << textureLife << std::endl;
    return ;
  }
  my_sprite.setTexture(*text);
  sprite.addTexture(text);
  for (int i = 0 ; i < lifes ; ++i)
  {
    my_sprite.setPosition(x, y);
    window.draw(my_sprite);
    x = x + 26;
  }
}

void Sfml::drawCharacter(int x, int y, const std::string & name_sprite)
{
  sprite.getSprite(name_sprite)->setPosition(x, y);
  window.draw(*(sprite.getSprite(name_sprite)));
}

void Sfml::display()
{
  window.display();
}

void Sfml::clearScreen()
{
  window.clear();
}

InputButton::id_button Sfml::getInput()
{
  while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed
	       || (event.type == sf::Event::KeyPressed
	        && event.key.code == sf::Keyboard::Escape))
    	{
    	  window.close();
    	  lastButtonPressed = InputButton::ECHAP;
        return lastButtonPressed;
    	}
      else if (event.type == sf::Event::KeyPressed)
	      {
	        if (buttons.find(event.key.code) != buttons.end())
	          lastButtonPressed = buttons[event.key.code];
          else if (event.key.code == sf::Keyboard::BackSpace)
          {
            if (name.size() > 0)
            name.resize(name.size() - 1);
            return InputButton::UNDEF;
          }
          else
          {
            if (name.length() < 3)
            {
              char map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
              if (event.key.code >= 0 && event.key.code < 26)
                name += map[event.key.code];
            }
            return InputButton::UNDEF;
          }
          return lastButtonPressed;
	      }
    }
  return InputButton::UNDEF;
}

void Sfml::close()
{
  if (sounds.find("pacman") != sounds.end())
    sounds["pacman"]->stop();
  else if (sounds.find("nibbler") != sounds.end())
    sounds["nibbler"]->stop();
  else if (sounds.find("centipede") != sounds.end())
    sounds["centipede"]->stop();
  window.close();
  lastButtonPressed = InputButton::UNDEF;
}

bool Sfml::needSprites() const
{
  return true;
}

int Sfml::getTileSize() const
{
  return tilesize;
}

void Sfml::drawHighScore(std::vector<std::string> scores, bool state)
{
  if (!state)
  {
    int i = 1;
    for (std::vector<std::string>::iterator it = scores.begin() ; it != scores.end() ; ++it)
    {
      std::stringstream s(*it);
      std::stringstream s1;

      int score;
      std::string playerName;

      s >> score >> playerName;
      s1 << i;
      sf::Text Text(s1.str(), fonts["score"], 25);
      Text.setPosition((width + 3) * tilesize , tilesize * (3 + i * 2));
      s1.str("");
      s1 << playerName;
      sf::Text Text1(s1.str(), fonts["score"], 25);
      Text1.setPosition(tilesize * (width + 4), tilesize * (3 + i * 2));
      s1.str("");
      s1 << score;
      sf::Text Text2(s1.str(), fonts["score"], 25);
      Text2.setPosition(tilesize * (width + 12), tilesize * (3 + i * 2));
      window.draw(Text);
      window.draw(Text1);
      window.draw(Text2);
      ++i;
    }
    return;
  }

  int i = 1;
  int x = 0;
  int y = 1000;
  bool second = true;
  sf::Font myFont;

  myFont.loadFromFile("font/Xperia.ttf");
  for (std::vector<std::string>::iterator it = scores.begin() ; it != scores.end() ; ++it)
  {
    std::stringstream s(*it);
    std::stringstream s1;

    int score;
    std::string playerName;

    s >> score >> playerName;
    sf::Text Text(std::to_string(i) + ".", myFont, 25);
    if (second)
      Text.setPosition(WINX / 2 - (Text.getLocalBounds().width) - tilesize * 8, y);
    else
      Text.setPosition(WINX / 2 + (Text.getLocalBounds().width) + tilesize * 2, y);
    sf::Text Text1(std::to_string(score), myFont, 25);
    if (second)
      Text1.setPosition(WINX / 2 - (Text.getLocalBounds().width) - tilesize * 5, y);
    else
      Text1.setPosition(WINX / 2 + (Text.getLocalBounds().width) + tilesize * 4, y);

    window.draw(Text1);
    window.draw(Text);
    ++i;
    if (i == 6)
    {
      y = 1000;
      second = false;
    }
    else
      y += tilesize * 2;

  }
}

InputButton::id_button
Sfml::displayMenu(std::list<std::string> const &games, std::list<std::string> const &libs, int game, int lib)
{
  sf::Texture text;
  sf::Vector2u textScales;
  sf::Font myFont;
  sf::Text myText;
  int width;
  int i = 0;
  int y = tilesize * 10;

  if (!text.loadFromFile("Sprites/menu_background.jpg"))
    return InputButton::UNDEF;
  if (!myFont.loadFromFile("font/Xperia.ttf"))
    return InputButton::UNDEF;
  textScales = text.getSize();
  sf::Sprite img;
  img.setTexture(text);
  img.setScale(sf::Vector2f((double)WINX / (double)textScales.x , (double)WINY / (double)textScales.y ));

  myText.setFont(myFont);
  myText.setString("ARCADE");
  myText.setCharacterSize(50);
  myText.setPosition(WINX / 2 - myText.getLocalBounds().width / 2, tilesize * 2);

  window.draw(img);
  window.draw(myText);
  for (std::list<std::string>::const_iterator it = games.begin() ; it != games.end() ; ++it)
  {
    myText.setString(it->c_str());
    myText.setCharacterSize(30);
    myText.setPosition(WINX / 2 - myText.getLocalBounds().width / 2, y);
    if (i == game)
      myText.setColor(sf::Color(255, 0, 0));
    else
      myText.setColor(sf::Color(255, 255, 255));
    window.draw(myText);
    y += tilesize * 3;
    ++i;
  }

  y += tilesize * 3;
  i = 0;
  for (std::list<std::string>::const_iterator it = libs.begin() ; it != libs.end() ; ++it)
  {
    myText.setString(it->c_str());
    myText.setCharacterSize(30);
    myText.setPosition(WINX / 2 - myText.getLocalBounds().width / 2, y);
    if (i == lib)
      myText.setColor(sf::Color(255, 0, 0));
    else
    myText.setColor(sf::Color(255, 255, 255));
    window.draw(myText);
    y += tilesize * 3;
    ++i;
  }

  y += tilesize * 2;
  myText.setString("Press any key to enter a NAME:");
  myText.setPosition(WINX / 2 - myText.getLocalBounds().width / 2, y);
  myText.setColor(sf::Color(255, 255, 255));
  window.draw(myText);
  y += tilesize * 2;
  myText.setString(name);
  myText.setPosition(WINX / 2 - myText.getLocalBounds().width / 2, y);
  window.draw(myText);
  return InputButton::UNDEF;
}

const std::string
Sfml::getName() const
{
   return (name);
}

void
Sfml::leave()
{
}

extern "C"
{
    IDynLib *create_lib()
    {
      return new Sfml();
    }
}
