#include <iostream>
#include <dlfcn.h>
#include "IDynLib.hh"
#include "Core.hh"
#include "Menu.hh"
#include "PacMan.hh"
#include "Nibbler.hh"

int   main(int ac, char **av)
{
   Menu Menu;

   if (ac == 1)
      {
         std::cerr << "Usage : ./arcade ./lib_arcade_XXX.so" << std::endl;
         return (1);
      }
   if (!Menu.init(std::string(av[1])))
      return (1);
   Menu.launch();
  // void      *dhandle;
  // IDynLib*  (*lib_creator)();
  // IDynLib   *lib;
  // IDynLib   *lib2;
  // Core core;
  // PacMan pacman;
  //
  //
  // // if (ac < 2)
  // //   {
  // //     std::cerr << "Usage : ./arcade ./Sfml.so" << std::endl;
  // //     return (1);
  // //   }
  // dhandle = dlopen("./lib_arcade_sfml.so", RTLD_LAZY);
  // if (dhandle == NULL)
  //   return (1);
  //
  // lib_creator = reinterpret_cast<IDynLib *(*)()>(dlsym(dhandle, "create_lib"));
  // if (lib_creator == NULL)
  //   {
  //     std::cerr << "Could not initialize library !" << std::endl;
  //     return (1);
  //   }
  // srand(time(0));
  // lib = lib_creator();
  // dhandle = dlopen("./lib_arcade_ncurses.so", RTLD_LAZY);
  // if (dhandle == NULL)
  //   return (1);
  //
  // lib_creator = reinterpret_cast<IDynLib *(*)()>(dlsym(dhandle, "create_lib"));
  // if (lib_creator == NULL)
  //   {
  //     std::cerr << "Could not initialize library !" << std::endl;
  //     return (1);
  //   }
  //  lib2 = lib_creator();
  //  core.addLib(lib2);
  //  core.addLib(lib);
  // core.addGame(&pacman);
  // core.playGame("ROBERT");
  // dlclose(dhandle);
  // return (0);
}
