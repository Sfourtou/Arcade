#ifndef SFML_HH_
#define SFML_HH_

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iomanip>
#include "arcade.hh"
#include "IDynLib.hh"
#include "Sprite.hh"

class Sfml : public IDynLib
{
private:
  sf::Event event;
  sf::RenderWindow window;
  InputButton::id_button lastButtonPressed;
  std::map<int, InputButton::id_button> buttons;
  Sprite sprite;
  int tilesize;
  std::string textureMap;
  std::string textureLife;
  std::map<std::string, sf::Font> fonts;
  std::string name;
  std::vector<sf::SoundBuffer *> buffers;
  std::map<std::string, sf::Music *> sounds;
  int width;
  int height;
public:
  Sfml();
  virtual void createWindows();
  virtual bool WindowIsOpen();
  virtual void drawScore(int score);
  virtual void drawText(const std::string & texte, int size);
  virtual void drawLifes(int);
  virtual void drawMap(int * , int, int);
  virtual void drawCharacter(int , int, const std::string &);
  virtual int getTileSize() const;
  virtual void display();
  virtual bool needSprites() const;
  virtual void close();
  virtual void addSprite(const std::string &, const std::string &, int , int);
  virtual void drawHighScore(std::vector<std::string>, bool);
  virtual void clearScreen();
  virtual void addFont(const std::string &, const std::string &);
  virtual void setNameTextureMap(const std::string &);
  virtual InputButton::id_button getInput();
  virtual void setNameTextureLife(const std::string &);
  virtual InputButton::id_button displayMenu(std::list<std::string> const &libs, std::list<std::string> const &games, int game, int lib);
  virtual const std::string getName() const;
  virtual void addSound(const std::string & type, const std::string & file);
  virtual void playSound(const std::string & type);
  virtual void setTileSize(int);
  virtual void leave();
};

#define WINX 1600
#define WINY 1500

#endif
