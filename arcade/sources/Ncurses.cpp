#include <unistd.h>
#include "Ncurses.hh"

void
Ncurses::MapDrawer::drawSquare(WINDOW *win, uint y, uint x, int color, std::string const &name)
{
   wattron(win, COLOR_PAIR(color));
   mvwprintw(win, y + 2, x + 2, name.c_str());
   wattroff(win, COLOR_PAIR(color));
}

void
Ncurses::MapDrawer::drawWall(WINDOW *win, uint y, uint x)
{
   wattron(win, COLOR_PAIR(COLOR_WALL));
   mvwprintw(win, y + 2, x + 2, "  ");
   wattroff(win, COLOR_PAIR(COLOR_WALL));
}

void
Ncurses::MapDrawer::drawEat(WINDOW *win, uint y, uint x)
{
   wattron(win, COLOR_PAIR(COLOR_EAT));
   mvwprintw(win, y + 2, x + 2, "* ");
   wattroff(win, COLOR_PAIR(COLOR_EAT));
}

void
Ncurses::MapDrawer::drawPacman(WINDOW *win, uint y, uint x)
{
   wattron(win, COLOR_PAIR(COLOR_PAC));
   mvwprintw(win, y + 2, x + 2, "PM");
   wattroff(win, COLOR_PAIR(COLOR_PAC));
}

void
Ncurses::MapDrawer::drawNothing(WINDOW *win, uint y, uint x)
{
  wattron(win, COLOR_PAIR(COLOR_NOTHING));
  mvwprintw(win, y + 2, x + 2, "  ");
  wattroff(win, COLOR_PAIR(COLOR_NOTHING));
}

void
Ncurses::MapDrawer::drawBig(WINDOW *win, uint y, uint x)
{
  wattron(win, COLOR_PAIR(COLOR_NOTHING));
  mvwprintw(win, y + 2, x + 2, "@ ");
  wattroff(win, COLOR_PAIR(COLOR_NOTHING));

}

Ncurses::Ncurses()
   : name(""), isOpen(false), tilesize(24)
{

}

Ncurses::~Ncurses()
{
   delwin(infoWin.win);
   delwin(scoreWin.win);
   delwin(gameWin.win);
   endwin();
}

void
Ncurses::setTileSize(int size)
{
   tilesize = size;
}

void
Ncurses::drawBorder(WINDOW *win)
{
   int x;
   int y;
   int i;

   getmaxyx(win, y, x);
   mvwprintw(win, 0, 0, "+");
   mvwprintw(win, y - 1, 0, "+");
   mvwprintw(win, 0, x - 1, "+");
   mvwprintw(win, y - 1, x - 1, "+");
   for (i = 1; i < (y - 1); i++)
   {
      mvwprintw(win, i, 0, "|");
      mvwprintw(win, i, x - 1, "|");
   }
   for (i = 1; i < (x - 1); i++)
   {
      mvwprintw(win, 0, i, "-");
      mvwprintw(win, y  - 1, i, "-");
   }
}

void
Ncurses::createWindows()
{
   int parent_x;
   int parent_y;

   initscr();
   noecho();
   keypad(stdscr, TRUE);
   nodelay(stdscr, TRUE);
   curs_set(false);
   start_color();
   use_default_colors();
   init_pair(COLOR_WALL, COLOR_BLACK, COLOR_BLUE);
   init_pair(COLOR_EAT, COLOR_WHITE ,COLOR_BLACK);
   init_pair(COLOR_PAC, COLOR_MAGENTA, COLOR_YELLOW);
   init_pair(COLOR_NOTHING, COLOR_WHITE, COLOR_BLACK);
   init_pair(COLOR_TITLE, COLOR_YELLOW, COLOR_BLACK);
   init_pair(COLOR_LIFE, COLOR_RED, COLOR_BLACK);
   init_pair(COLOR_REDG, COLOR_BLACK, COLOR_RED);
   init_pair(COLOR_WHITEG, COLOR_BLACK, COLOR_WHITE);
   init_pair(COLOR_FRIG, COLOR_BLUE, COLOR_WHITE);
   init_pair(COLOR_CYANG, COLOR_BLACK, COLOR_CYAN);
   init_pair(COLOR_GREENG, COLOR_BLACK, COLOR_GREEN);
   init_pair(COLOR_MAGENTAG, COLOR_BLACK, COLOR_MAGENTA);
   init_pair(COLOR_NORMAL, COLOR_WHITE, COLOR_MAGENTA);

   isOpen = true;
   getmaxyx(stdscr, parent_y, parent_x);
   gameWin.win = newwin(3 * parent_y / 4, 3 * parent_x / 4, 0, 0);
   scoreWin.win = newwin(parent_y, parent_x / 4, 0, 3 * parent_x / 4);
   infoWin.win = newwin(parent_y / 4, 3 * parent_x / 4, 3 * parent_y / 4, 0);
   refresh();
   drawBorder(infoWin.win);
   drawBorder(scoreWin.win);
   drawBorder(gameWin.win);
   gameWin.name = "Game";
   scoreWin.name = "Score";
   infoWin.name = "Info";
   mvwprintw(gameWin.win, 0, 2, gameWin.name.c_str());
   mvwprintw(scoreWin.win, 0, 2, scoreWin.name.c_str());
   mvwprintw(infoWin.win, 0, 2, infoWin.name.c_str());
   wrefresh(infoWin.win);
   wrefresh(scoreWin.win);
   wrefresh(gameWin.win);
}

bool
Ncurses::WindowIsOpen()
{
   return (isOpen);
}

void
Ncurses::drawMap(int *map, int width, int height)
{
   for (uint i = 0; i < height * width; i++)
   {
      if (map[i] == 0 || map[i] == 98 || map[i] == 99)
         MapDrawer::drawNothing(gameWin.win, i / width, i % width * 2);
      else if (map[i] == 30)
        MapDrawer::drawEat(gameWin.win, i / width, i % width * 2);
      else if (map[i] == 28)
         MapDrawer::drawBig(gameWin.win, i / width, i % width * 2);
      else if (map[i] == 29)
         MapDrawer::drawNothing(gameWin.win, i / width, i % width * 2);
      else if (map[i] < 28)
         MapDrawer::drawWall(gameWin.win, i / width, i % width * 2);
      else
         MapDrawer::drawNothing(gameWin.win, i / width, i % width * 2);
   }
}

void
Ncurses::drawScore(int score)
{
   mvwprintw(infoWin.win, 1, 3, ("Score: " + std::to_string(score)).c_str());
   refresh();
   wrefresh(infoWin.win);
}


void
Ncurses::drawText(const std::string &text, int size)
{
   int y;
   int x;

   getmaxyx(scoreWin.win, y, x);
   x /= 2;
   x -= text.size() / 2;
   wattron(scoreWin.win, COLOR_PAIR(COLOR_TITLE));
   mvwprintw(scoreWin.win, 1, x, text.c_str());
   wattroff(scoreWin.win, COLOR_PAIR(COLOR_TITLE));
}

void
Ncurses::drawLifes(int lifes)
{
   int x;
   int yy;

   getmaxyx(infoWin.win, yy, x);
   x -= 15;
   wattron(infoWin.win, COLOR_PAIR(COLOR_LIFE));
   mvwprintw(infoWin.win, 1, x, ("Lifes: " + std::to_string(lifes)).c_str());
   wattroff(infoWin.win, COLOR_PAIR(COLOR_LIFE));
}

int
Ncurses::getTileSize() const
{
  return (tilesize);
}

void
Ncurses::addSprite(const std::string __attribute__((unused)) &toto, const std::string __attribute__((unused)) &titi, int __attribute__((unused)) x, int __attribute__((unused)) y)
{

}

InputButton::id_button
Ncurses::getInput()
{
   std::map<int, InputButton::id_button> tab;
   int key;

   key = -1;
   tab[-1] = InputButton::UNDEF;
   tab[KEY_UP] = InputButton::UP;
   tab[KEY_DOWN] = InputButton::DOWN;
   tab[KEY_RIGHT] = InputButton::RIGHT;
   tab[KEY_LEFT] = InputButton::LEFT;
   tab[27] = InputButton::ECHAP;
   tab[' '] = InputButton::SPACE;
   tab['\n'] = InputButton::ENTER;
   tab['9'] = InputButton::NINE;
   tab['8'] = InputButton::EIGHT;
   tab['2'] = InputButton::TWO;
   tab['3'] = InputButton::THREE;
   tab['4'] = InputButton::FOUR;
   tab['5'] = InputButton::FIVE;
   key = getch();
   if (key == 27)
   {
      endwin();
      isOpen = false;
   }
   if (tab.find(key) == tab.end() && name.size() < 3)
     name += key;
   return (tab[key]);
}

void
Ncurses::drawCharacter(int x, int y, UU const std::string & name_sprite)
{
   std::string start;

   start = name_sprite.substr(0, 3);
   if (start == "pac")
      MapDrawer::drawPacman(gameWin.win, y / tilesize, x / (tilesize / 2));
   else if (start == "Red")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_REDG, name_sprite == "RedFruit"? "  " : "bl");
   else if (start == "Cen")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_REDG, "  ");
   else if (start == "Ora")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_MAGENTAG, "sp");
   else if (start == "Sho")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_TITLE, "||");
   else if (start == "Blu")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_CYANG, name_sprite == "BlueShip" ? "  " : "in");
   else if (start == "Mar")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_GREENG, "cl");
   else if (start == "Fri")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_FRIG, "><");
   else if (start == "Whi")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_WHITEG, "><");
   else if (start == "Eye")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_NORMAL, "oo");
   else if (start == "Gre")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_GREENG, "  ");
   else if (start == "FMu")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_WHITEG, "  ");
   else if (start == "TMu")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_EAT, "x ");
   else if (start == "HMu")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_EAT, "* ");
   else if (start == "QMu")
      MapDrawer::drawSquare(gameWin.win, y / tilesize, x / (tilesize / 2), COLOR_EAT, "` ");
}

void
Ncurses::display()
{
   wrefresh(infoWin.win);
   wrefresh(gameWin.win);
   refresh();
}

void
Ncurses::close()
{
   endwin();
   isOpen = false;
}

void
Ncurses::clearScreen()
{
}

bool
Ncurses::needSprites() const
{
   return (false);
}
void
Ncurses::drawHighScore(std::vector<std::string> scores, bool state)
{
   int i = 1;
   int x = 0;
   int y = 0;

   int score;
   std::string playerName;

   getmaxyx(scoreWin.win, y, x);
   for (std::vector<std::string>::iterator it = scores.begin(); it != scores.end(); ++it)
   {
      std::stringstream s(*it);
      s >> score >> playerName;
      for (int j = 1; j < (x - 1); ++j)
         mvwprintw(scoreWin.win, (i + 1) * 2,  j, " ");
      mvwprintw(scoreWin.win, (i + 1) * 2, x / 2 - (it->size() / 2), (std::to_string(i) + ": " + playerName + " " + std::to_string(score)).c_str());
      ++i;
   }
   wrefresh(scoreWin.win);
   refresh();
}

void
Ncurses::setNameTextureMap(const std::string &toto)
{
   (void)toto;
}

void
Ncurses::setNameTextureLife(const std::string &toto)
{
   (void)toto;
}

void
Ncurses::addFont(const std::string &toto, const std::string &titi)
{
   (void)toto;
   (void)titi;
}

InputButton::id_button
Ncurses::displayMenu(std::list<std::string> const &libs, std::list<std::string> const &games, int game, int lib)
{
   int i;
   int x;
   int y;

   i = 0;
   getmaxyx(infoWin.win, y, x);
   for (std::list<std::string>::const_iterator it = games.begin(); it != games.end(); ++it)
   {
      if (i == lib)
         mvwprintw(infoWin.win, (i * 2) + 3, x / 2 - (it->size() / 2) - 10, "--->");
      else
         mvwprintw(infoWin.win, (i * 2) + 3, x / 2 - (it->size() / 2) - 10, "    ");
      mvwprintw(infoWin.win, (i * 2) + 3, x / 2 - (it->size() / 2), it->c_str());
      ++i;
   }
   i = 0;
   getmaxyx(infoWin.win, y, x);
   for (std::list<std::string>::const_iterator it = libs.begin(); it != libs.end(); ++it)
   {
      if (i == game)
         mvwprintw(gameWin.win, (i * 2) + 3, x / 2 - (it->size() / 2) - 10, "--->");
      else
         mvwprintw(gameWin.win, (i * 2) + 3, x / 2 - (it->size() / 2) - 10, "    ");
      mvwprintw(gameWin.win, (i * 2) + 3, x / 2 - (it->size() / 2), it->c_str());
      ++i;
   }
   mvwprintw(infoWin.win, y - 2, x / 2 + ((10 - name.size()) / 2), (std::string("| NAME: ") + name + std::string(" |")).c_str());
   wrefresh(infoWin.win);
   wrefresh(gameWin.win);
   refresh();
}

const std::string
Ncurses::getName() const
{
   return (name);
}

void
Ncurses::addSound(UU const std::string & type, UU const std::string & file)
{
}

void
Ncurses::playSound(UU const std::string & type)
{
}

void
Ncurses::leave()
{
   int x;
   int y;

   getmaxyx(infoWin.win, y, x);
   for (int tmpy = 0; tmpy < y; ++tmpy)
   {
      for (int tmpx = 0; tmpx < x; ++tmpx)
         mvwprintw(infoWin.win, tmpy, tmpx, " ");
   }
   getmaxyx(gameWin.win, y, x);
   for (int tmpy = 0; tmpy < y; ++tmpy)
   {
      for (int tmpx = 0; tmpx < x; ++tmpx)
         mvwprintw(gameWin.win, tmpy, tmpx, " ");
   }
   getmaxyx(scoreWin.win, y, x);
   for (int tmpy = 0; tmpy < y; ++tmpy)
   {
      for (int tmpx = 0; tmpx < x; ++tmpx)
         mvwprintw(scoreWin.win, tmpy, tmpx, " ");
   }
   refresh();
   wrefresh(infoWin.win);
   wrefresh(scoreWin.win);
   wrefresh(gameWin.win);
   drawBorder(infoWin.win);
   drawBorder(scoreWin.win);
   drawBorder(gameWin.win);
}

extern "C"
{
  IDynLib *create_lib()
  {
    return new Ncurses();
  }
}
