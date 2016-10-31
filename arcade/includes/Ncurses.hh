#ifndef NCURSES_HH_
# define NCURSES_HH_

#include <iostream>
#include <curses.h>
#include <sstream>
#include <map>
#include <string>
#include "IDynLib.hh"
#include "arcade.hh"

# define WINX 1200
# define WINY 800

# define GAME_WIN_Y_OFF 0
# define GAME_WIN_Y 3 * WINY / 4
# define GAME_WIN_X WINX

# define INFO_WIN_Y_OFF GAME_WIN_Y
# define INFO_WIN_Y WINY / 4
# define INFO_WIN_X WINX

# define COLOR_WALL  1
# define COLOR_EAT   2
# define COLOR_PAC   3
# define COLOR_NOTHING 4
# define COLOR_TITLE 5
# define COLOR_LIFE 6
# define COLOR_REDG 7
# define COLOR_WHITEG 8
# define COLOR_MAGENTAG 9
# define COLOR_GREENG 10
# define COLOR_CYANG 11
# define COLOR_FRIG 12
# define COLOR_NORMAL 15

class Ncurses : public IDynLib
{
public:
   struct Win
   {
      WINDOW      *win;
      std::string name;
   };
   struct MapDrawer
   {
      static void drawSquare(WINDOW *win, uint y, uint x, int color, std::string const &name);
      static void drawWall(WINDOW *win, uint y, uint x);
      static void drawEat(WINDOW *win, uint y, uint x);
      static void drawPacman(WINDOW *win, uint y, uint x);
      static void drawNothing(WINDOW *win, uint y, uint x);
      static void drawBig(WINDOW *win, uint y, uint x);
   };
   Ncurses();
   ~Ncurses();
   virtual void createWindows();
   virtual bool WindowIsOpen();
   virtual void drawScore(int score);
   virtual void drawText(const std::string & texte, int size);
   virtual void drawLifes(int lifes);
   virtual void drawMap(int *map , int width, int height);
   virtual int getTileSize() const;
   virtual void addSprite(const std::string &, const std::string &, int, int);
   virtual void display();
   virtual bool needSprites() const;
   virtual void close();
   virtual void clearScreen();
   virtual void drawCharacter(int , int, const std::string &);
   virtual void drawHighScore(std::vector<std::string>, bool);
   virtual void setNameTextureMap(const std::string &);
   virtual void addFont(const std::string &, const std::string &);
   virtual InputButton::id_button getInput();
   virtual void setNameTextureLife(const std::string &);
   virtual InputButton::id_button displayMenu(std::list<std::string> const &libs, std::list<std::string> const &games, int game, int lib);
   virtual const std::string getName() const;
   virtual void addSound(const std::string & type, const std::string & file);
   virtual void playSound(const std::string & type);
   virtual void setTileSize(int);
   virtual void leave();
private:
   std::string name;
   bool isOpen;
   Ncurses::Win gameWin;
   Ncurses::Win infoWin;
   Ncurses::Win scoreWin;
   void initTextureMap();
   void drawBorder(WINDOW *win);
   int tilesize;
};


#endif /* !Ncurses.hh */
