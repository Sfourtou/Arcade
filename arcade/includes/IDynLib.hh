#ifndef IDYNLIB_HH_
#define IDYNLIB_HH_

#include <list>
#include "arcade.hh"
#include "Map.hh"

class IDynLib
{
protected:

  public:
    virtual void createWindows() = 0;
    virtual bool WindowIsOpen() = 0;
    virtual void drawScore(int score) = 0;
    virtual void drawText(const std::string & texte, int size) = 0;
    virtual void drawLifes(int lifes) = 0;
    virtual void drawMap(int *, int, int) = 0;
    virtual int getTileSize() const = 0;
    virtual void addSprite(const std::string &, const std::string &, int, int) = 0;
    virtual void display() = 0;
    virtual bool needSprites() const = 0;
    virtual void close() = 0;
    virtual void clearScreen() = 0;
    virtual void drawCharacter(int, int , const std::string &) = 0;
    virtual void drawHighScore(std::vector<std::string>, bool) = 0;
    virtual void setNameTextureMap(const std::string &) = 0;
    virtual void addFont(const std::string &, const std::string &) = 0;
    virtual InputButton::id_button getInput() = 0;
    virtual void setNameTextureLife(const std::string &) = 0;
    virtual InputButton::id_button displayMenu(std::list<std::string> const &libs, std::list<std::string> const &games, int game, int lib) = 0;
    virtual const std::string getName() const = 0;
    virtual void addSound(const std::string & type, const std::string & file) = 0;
    virtual void playSound(const std::string & type) = 0;
    virtual void setTileSize(int) = 0;
    virtual void leave() = 0;
};

#endif
