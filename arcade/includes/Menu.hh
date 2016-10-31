#ifndef MENU_HH_
# define MENU_HH_
# include <iostream>
# include <dlfcn.h>
# include <sys/types.h>
# include <dirent.h>
# include <string>
# include <cstdlib>
# include "Centipede.hh"
# include "PacMan.hh"
# include "Nibbler.hh"
# include "IDynLib.hh"
# include "Core.hh"

# define LIB_PATH "./lib/"
# define GAME_PATH "./games/"
# define START_LIB "lib_arcade_"
# define START_GAME "game_arcade_"

class Menu
{
public:
   Menu();
   ~Menu();
   int init(std::string const &libname);
   void launch();
private:
   Core core;
   IDynLib *showLib;
   std::list<std::string> games;
   std::list<std::string> libs;
   std::list<void *> sharedLibs;
   int getGames();
   int getLibraries(std::string const &libname);
   void close();
};

#endif
