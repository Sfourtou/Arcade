#include <sstream>
#include <SDL/SDL_ttf.h>
#include "Opengl.hh"

Opengl::Opengl()
{
  buttons[SDLK_UP] = InputButton::UP;
  buttons[SDLK_DOWN] = InputButton::DOWN;
  buttons[SDLK_RIGHT] = InputButton::RIGHT;
  buttons[SDLK_LEFT] = InputButton::LEFT;
  buttons[SDLK_ESCAPE] = InputButton::ECHAP;
  buttons[SDLK_SPACE] = InputButton::SPACE;
  buttons[SDLK_RETURN] = InputButton::ENTER;
  buttons[SDLK_2] = InputButton::TWO;
  buttons[SDLK_3] = InputButton::THREE;
  buttons[SDLK_4] = InputButton::FOUR;
  buttons[SDLK_5] = InputButton::FIVE;
  buttons[SDLK_8] = InputButton::EIGHT;
  buttons[SDLK_9] = InputButton::NINE;

  isOpen = false;

  eyeX = 0;
  eyeY = 22;
  eyeZ = 0;
  angle = 2;
  visX = sin(0);
  visY = -3;
  visZ = -cos(0);
  tilesize = 24;
  widthMap = 0;
  heightMap = 0;
  name = "";
  lastButtonPressed = InputButton::UNDEF;
  int ac = 1;
   char name[] = "arcade";
  char *argv[] = {name, NULL};
    glutInit(&ac, argv);
}

void Opengl::setTileSize(int size)
{
  tilesize = size;
}

void Opengl::addSound(UU const std::string & type, UU const std::string & file)
{
}

void Opengl::playSound(UU const std::string & tyoe)
{
}

void Opengl::createWindows()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Arcade", NULL);
  SDL_SetVideoMode(WINX, WINY, 32, SDL_OPENGL);
  SDL_EnableKeyRepeat(50, 50);
  glEnable(GL_DEPTH_TEST);
  lastButtonPressed = InputButton::UNDEF;
  TTF_Init();
  atexit(TTF_Quit);
  atexit(SDL_Quit);

  isOpen = true;
}

bool Opengl::WindowIsOpen()
{
  return isOpen;
}

void Opengl::drawMap(int *map, int width, int height)
{
  int i;

  i = -1;
  if (widthMap != width || heightMap != height)
  {
    eyeZ = (double)height * 3 / 10;
    widthMap = width;
    heightMap = height;
  }
  while (++i < width * height)
  {
    if (map[i] < 28 && map[i] != 0)
    {
      glColor3ub(0, 0, 255);
      drawCube((i % width) * 1, (i / width) * 1);
    }
    if (map[i] == 30)
    {
      glColor3ub(255, 204, 11);
      drawSphere((i % width) * 1, (i / width) * 1, 0.15);
    }
     if (map[i] == 29)
     {
       glColor3ub(255, 255, 11);
       drawSphere((i % width) * 1, (i / width) * 1, 0.2);
     }
  }
}

void renderText(std::string text, SDL_Color color, int x, int y, int size)
{
  int xFont;
  int yFont;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, WINX, 0, WINY);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glRotated(180, 1, 0, 0);

  TTF_Font * font = TTF_OpenFont("./font/Xperia.ttf", size);
  SDL_Surface * sFont;

  sFont = TTF_RenderText_Blended(font, text.c_str() , color);
  TTF_SizeText(font, text.c_str(), &xFont, &yFont);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
  x = WINX / 2 - xFont / 2;
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,0); glVertex2f(x, y);
    glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
    glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
    glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glDeleteTextures(1, &texture);
  TTF_CloseFont(font);
  SDL_FreeSurface(sFont);
}


void Opengl::drawScore(int score)
{
}
void Opengl::drawText(const std::string & texte, int size)
{

}

void Opengl::drawLifes(int lifes)
{
}

int Opengl::getTileSize() const
{
  return tilesize;
}

void Opengl::addSprite(const std::string &, const std::string &, int, int)
{
}

void Opengl::display()
{
  glFlush();
  SDL_GL_SwapBuffers();
}

bool Opengl::needSprites() const
{
  return false;
}

void Opengl::close()
{
  isOpen = false;
  SDL_Quit();
}

void Opengl::clearScreen()
{
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)WINX/WINY, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, eyeX + visX, eyeY + visY, eyeZ + visZ, 0, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Opengl::drawCharacter(int x, int y, const std::string &name)
{
  std::string start;

  start = name.substr(0, 3);
  if (start == "pac")
     glColor3ub(255, 204, 11);
  else if (start == "Red")
    glColor3ub(255, 0, 0);
  else if (start == "Ora")
    glColor3ub(255, 153, 204);
  else if (start == "Sho")
    glColor3ub(255, 255, 0);
  else if (start == "Blu")
    glColor3ub(0, 255, 255);
  else if (start == "Mar")
    glColor3ub(255, 153, 51);
  else if (start == "Fri")
    glColor3ub(0, 128, 255);
  else if (start == "Whi")
    glColor3ub(255, 255, 255);
  else if (start == "Eye")
    glColor3ub(255, 255, 255);
  else if (start == "Gre" || start == "Cen")
    glColor3ub(0, 200, 0);
  else if (start == "FMu")
    glColor3ub(255, 153, 51);
  else if (start == "TMu")
    glColor3ub(255, 153, 51);
  else if (start == "HMu")
    glColor3ub(255, 153, 51);
  else if (start == "QMu")
    glColor3ub(255, 153, 51);

    if (name.find("Ghost") != std::string::npos)
      drawGhost((double)x / tilesize, (double)y / tilesize);
    else if (name.find("Snake") != std::string::npos || name.find("Centi") != std::string::npos)
      drawCube((double)x / tilesize, (double)y / tilesize);
    else if (name.find("QMush") != std::string::npos)
      drawWireSphere((double)x / tilesize, (double)y/ tilesize, 0.5);
    else if (name.find("HMush") != std::string::npos)
      drawSphere((double)x / tilesize, (double)y/ tilesize, 0.5);
    else if (name.find("TMush") != std::string::npos)
    {
      drawWireCube((double)x / tilesize, (double)y / tilesize);
      drawSphere((double)x / tilesize, (double)y/ tilesize, 0.5);
    }
    else if (name.find("FMush") != std::string::npos)
      drawCube((double)x / tilesize, (double)y / tilesize);
    else if (name.find("Ship") != std::string::npos)
      drawTetra((double)x / tilesize, (double)y / tilesize);
    else if (name.find("Shoot") != std::string::npos)
      drawCyl((double)x / tilesize, (double)y / tilesize);
    else
    drawSphere((double)x / tilesize, (double)y/ tilesize, 0.5);
}

void Opengl::drawHighScore(std::vector<std::string> scores, bool state)
{
  if (state == false)
    return;
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  SDL_Color color = {255, 255, 255, 0};
  int x = 5;
  int y = 10;
  int size = 50;
  int i = 1;

  gluOrtho2D(0, WINX, 0, WINY);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glRotated(180, 1, 0, 0);

  TTF_Font * font = TTF_OpenFont("./font/Xperia.ttf", 30);
  SDL_Surface * sFont;

  y = 410;
  for (std::vector<std::string>::iterator it = scores.begin() ; it != scores.end() ; ++it)
  {
    std::stringstream s(*it);
    int score;
    std::string name;

    s >> score >> name;
    std::string concat = std::to_string(i) +  ". " + std::to_string(score);
    sFont = TTF_RenderText_Blended(font,  concat.c_str(), color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
    glBegin(GL_QUADS);
    {
      glTexCoord2f(0,0); glVertex2f(x, y);
      glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
      glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
      glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
    }
    glEnd();
    ++i;
    if (i == 6)
    {
      x = 200;
      y = 410;
    }
    else
      y = y + 40;
  }
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glDeleteTextures(1, &texture);
  TTF_CloseFont(font);
  SDL_FreeSurface(sFont);
}

void Opengl::setNameTextureMap(const std::string &name)
{
}

void Opengl::addFont(const std::string & f, const std::string & g)
{
}

InputButton::id_button Opengl::getInput()
{
  if (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT
      || (event.type == SDL_KEYDOWN
        && event.key.keysym.sym == SDLK_ESCAPE))
    {
      close();
      return InputButton::ECHAP;
    }
    if (event.type == SDL_KEYDOWN)
    {
      gereCamera(event.key.keysym.sym);
      if (buttons.find(event.key.keysym.sym) != buttons.end())
      {
       lastButtonPressed = buttons[event.key.keysym.sym];
       return lastButtonPressed;
      }
      else if (event.key.keysym.sym == SDLK_BACKSPACE)
        name.pop_back();
      else if (name.size() < 3)
        name.push_back((char)event.key.keysym.sym);
    }
  }
  return InputButton::UNDEF;
}

void Opengl::setNameTextureLife(const std::string &name)
{
}

InputButton::id_button Opengl::displayMenu(std::list<std::string> const &libs, std::list<std::string> const &games, int game, int lib)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  SDL_Color color = {255, 255, 255, 0};
  std::string message = std::string("Hello World");
  int x = 5;
  int y = 10;
  int xFont;
  int yFont;
  int size = 50;
  int i = 0;

  gluOrtho2D(0, WINX, 0, WINY);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glRotated(180, 1, 0, 0);

  TTF_Font * font = TTF_OpenFont("./font/Xperia.ttf", size);
  SDL_Surface * sFont;

  sFont = TTF_RenderText_Blended(font, "ARCADE" , color);
  TTF_SizeText(font, "ARCADE", &xFont, &yFont);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
  x = WINX / 2 - xFont / 2;
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,0); glVertex2f(x, y);
    glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
    glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
    glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
  }
  glEnd();


  y += 150;
  x = 20;
  font = TTF_OpenFont("./font/Xperia.ttf", 30);
  for (std::list<std::string>::const_iterator it = libs.begin() ; it != libs.end() ; ++it)
  {
    if (i == game)
      color = {255, 0, 0, 0};
    else
      color = {255, 255, 255, 0};

    sFont = TTF_RenderText_Blended(font, (*it).c_str() , color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
    glBegin(GL_QUADS);
    {
      glTexCoord2f(0,0); glVertex2f(x, y);
      glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
      glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
      glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
    }
    glEnd();
    y += 40;
    ++i;
  }
  x = 350;
  y = 160;
  i = 0;
  for (std::list<std::string>::const_iterator it = games.begin() ; it != games.end() ; ++it)
  {
    if (i == lib)
      color = {255, 0, 0, 0};
    else
      color = {255, 255, 255, 0};
    sFont = TTF_RenderText_Blended(font, (*it).c_str() , color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    glBegin(GL_QUADS);
    {
      glTexCoord2f(0,0); glVertex2f(x, y);
      glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
      glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
      glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
    }
    glEnd();
    y += 40;
    ++i;
  }

  color = {255, 255, 255, 0};
  x = 5;
  y = 325;
  std::string my_name = "Please enter your name : " + name;
  sFont = TTF_RenderText_Blended(font, my_name.c_str() , color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,0); glVertex2f(x, y);
    glTexCoord2f(1,0); glVertex2f(x + sFont->w, y);
    glTexCoord2f(1,1); glVertex2f(x + sFont->w, y + sFont->h);
    glTexCoord2f(0,1); glVertex2f(x, y + sFont->h);
  }
  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glDeleteTextures(1, &texture);
  TTF_CloseFont(font);
  SDL_FreeSurface(sFont);
}
const std::string Opengl::getName() const
{
  return name;
}

void Opengl::gereCamera(int key) {
  switch (key)
  {
    case SDLK_w:
      eyeX += visX * 0.1;
      eyeZ += visZ * 0.1;
      break;
    case SDLK_s:
      eyeX -= visX * 0.1;
      eyeZ -= visZ * 0.1;
    break;
    case SDLK_a:
      eyeX -= 0.1;
      break;
    case SDLK_d:
       eyeX += 0.1;
    break;
    }
}

void Opengl::drawCyl(double x, double y)
{
  glEnable(GL_COLOR_MATERIAL);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLUquadric *params;
  params = gluNewQuadric();
  gluQuadricDrawStyle(params, GLU_LINE);
  gluQuadricNormals(params, GLU_SMOOTH);
  gluCylinder(params, 0.1, 0.1, 1, 16, 16);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
}

void Opengl::drawCube(double x, double y)
{
  glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  glutSolidCube(1);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
}

void Opengl::drawWireCube(double x, double y)
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  glutWireCube(1);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
}

void Opengl::drawGhost(double x, double y)
{
  glEnable(GL_COLOR_MATERIAL);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  glRotated(-90, 1, 0, 0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLUquadric *params;
  params = gluNewQuadric();
  gluQuadricDrawStyle(params, GLU_FILL);
  gluQuadricNormals(params, GLU_SMOOTH);
  gluCylinder(params, 0.5, 0.5, 1, 32, 32);
  glTranslated(0, 0, 1);
  gluSphere(params, 0.5, 32, 32);
  glTranslated(0, 0, -1);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glRotated(90, 1, 0, 0);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
}

void Opengl::drawWireSphere(double x, double y, double size)
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  GLUquadric *params;
  params = gluNewQuadric();
  gluQuadricDrawStyle(params, GLU_POINT);
  gluQuadricNormals(params, GLU_SMOOTH);
  gluSphere(params, size, 16, 16);
  gluDeleteQuadric(params);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
}

void Opengl::drawTetra(double x, double y)
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  glRotated(90, 0, 1, 0);
  glutSolidTetrahedron();
  glRotated(-90, 0, 1, 0);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
}

void Opengl::drawSphere(double x, double y, double size)
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glTranslated(-widthMap/2 + x, 0, -heightMap/2 + y);
  GLUquadric *params;
  params = gluNewQuadric();
  gluQuadricDrawStyle(params, GLU_FILL);
  gluQuadricNormals(params, GLU_SMOOTH);
  gluSphere(params, size, 32, 32);
  gluDeleteQuadric(params);
  glTranslated(widthMap/2 - x, 0, heightMap/2 - y);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
}

void Opengl::leave()
{
}

extern "C"
{
    IDynLib *create_lib()
    {
      return new Opengl();
    }
}
