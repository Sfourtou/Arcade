#ifndef OPENGL_HH_
#define OPENGL_HH_

#include <iostream>
#include <map>
#include "arcade.hh"
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#ifdef __APPLE__
 #include <OpenGL/gl.h>
 #include <OpenGL/glu.h>
 #include <GLUT/glut.h>
 #include <OpenGL/glext.h>
#else
 #include <GL/gl.h>
 #include <GL/glu.h>
 #include <GL/glut.h>
 #include <GL/glext.h>
#endif
#include "IDynLib.hh"
#include "Sprite.hh"

class Opengl : public IDynLib
{
private:
  double eyeX;
  double eyeY;
  double eyeZ;
  double angle;
  double visX;
  double visY;
  double visZ;

  SDL_Event event;
  bool      isOpen;
  InputButton::id_button lastButtonPressed;
  std::map<int, InputButton::id_button> buttons;
  int tilesize;
  int widthMap;
  int heightMap;
  std::string name;
// GLFWwindow* window;
public:
  Opengl();
  virtual void createWindows();
  virtual bool WindowIsOpen();
  virtual void drawMap(int *, int, int);
  virtual void drawScore(int score);
  virtual void drawText(const std::string & texte, int size);
  virtual void drawLifes(int lifes);
  virtual int getTileSize() const;
  virtual void addSprite(const std::string &, const std::string &, int, int);
  virtual void display();
  virtual bool needSprites() const;
  virtual void close();
  virtual void clearScreen();
  virtual void drawCharacter(int, int , const std::string &);
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
  void drawCube(double x, double y);
  void drawSphere(double x, double y, double size);
  void gereCamera(int);
  void drawGhost(double x, double y);
  void drawWireCube(double x, double y);
  void drawWireSphere(double x, double y, double size);
  void drawTetra(double x, double y);
  void drawCyl(double x, double y);
};

#define WINX 800
#define WINY 600

#endif
