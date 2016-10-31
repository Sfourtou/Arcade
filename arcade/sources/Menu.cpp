#include "Menu.hh"

Menu::Menu()
   : showLib(0)
{

}

Menu::~Menu()
{

}

int
Menu::getLibraries(std::string const &libname)
{
   DIR     *stream;
   struct dirent *d;
   void *dhandle;
   IDynLib *(*lib_creator)();
   IDynLib *lib;

   if (!(stream = opendir(LIB_PATH)))
   {
      std::cerr << "Failed to open current directory" << std::endl;
      return (0);
   }
   while ((d = readdir(stream)))
   {
      if (std::string(d->d_name).substr(0, 11) == START_LIB)
      {
         if (!(dhandle = dlopen((LIB_PATH + std::string(d->d_name)).c_str(), RTLD_LAZY)))
         {
            std::cerr << "Failed to open graphic lib" << std::endl;
            return (0);
         }
         sharedLibs.push_back(dhandle);
         if (!(lib_creator = reinterpret_cast<IDynLib *(*)()>(dlsym(dhandle, "create_lib"))))
         {
            std::cerr << "Could not initialize library !" << std::endl;
            return (0);
         }
         lib = lib_creator();
         if (LIB_PATH + std::string(d->d_name) == libname || LIB_PATH + std::string(d->d_name) == libname)
            showLib = lib;
         libs.push_back(std::string(d->d_name));
         core.addLib(lib);
      }
   }
   closedir(stream);
   if (!showLib)
   {
      std::cerr << "Parameter lib not found" << std::endl;
      return (0);
   }
   return (1);
}

int
Menu::getGames()
{
   DIR     *stream;
   struct dirent *d;
   void *dhandle;
   AGame *(*game_creator)();
   AGame * game;

   if (!(stream = opendir(GAME_PATH)))
   {
      std::cerr << "Failed to open game directory" << std::endl;
      return (0);
   }
   while ((d = readdir(stream)))
   {

      if (std::string(d->d_name).substr(0, 11) == START_LIB)
      {
         if (!(dhandle = dlopen((GAME_PATH + std::string(d->d_name)).c_str(), RTLD_LAZY)))
         {
            std::cerr << "Failed to open game lib" << std::endl;
            return (0);
         }
         sharedLibs.push_back(dhandle);
         if (!(game_creator = reinterpret_cast<AGame *(*)()>(dlsym(dhandle, "create_game"))))
         {
            std::cerr << "Could not initialize library !" << std::endl;
            return (0);
         }
         game = game_creator();
         games.push_back(game->getName());
         core.addGame(game);
      }
   }
   return (1);
}

int
Menu::init(std::string const &libname)
{
   srand(time(0));
   if (!getLibraries(libname))
      return (0);
   getGames();
   return (1);
}

void
Menu::launch()
{
   std::string name;
   Score score;
   InputButton::id_button pressedButton;
   int idxLib = 0;
   int idxGame = 0;
   int ret = 1;
   bool currentList = false;
   int tmp;

   showLib->createWindows();
   while (ret == 1)
      {
         tmp = 0;
         for (std::list<std::string>::iterator it = games.begin(); it != games.end(); ++it)
            {
               if (tmp == idxGame)
                //try {
                  score.load(std::string("scores/") + *it + std::string(".score"), 10);
                //} throw (std::Exception e)
                //{
              //    return ();
            //    }
               ++tmp;
            }
         showLib->displayMenu(games, libs, idxGame, idxLib);
         name = showLib->getName();
         showLib->drawHighScore(score.getHighScores(), true);
         showLib->display();
         pressedButton = showLib->getInput();
         if (pressedButton == InputButton::UP)
         {
            if (!currentList)
               idxGame = idxGame - 1 < 0 ? games.size() - 1: idxGame - 1;
            else
               idxLib = idxLib - 1 < 0 ? libs.size() - 1: idxLib - 1;
         }
         else if (pressedButton == InputButton::DOWN)
         {
            if (!currentList)
               idxGame = idxGame + 1 > games.size() - 1 ? 0 : idxGame + 1;
            else
               idxLib = idxLib + 1 > libs.size() - 1 ? 0 : idxLib + 1;
         }
         else if (pressedButton == InputButton::RIGHT || pressedButton == InputButton::LEFT)
            currentList = !currentList;
         else if (pressedButton == InputButton::ECHAP)
         {
            showLib->close();
            ret = 0;
         }
         else if (pressedButton == InputButton::ENTER)
         {
            showLib->close();
            core.setIdxLib(idxLib);
            core.setIdxGame(idxGame);
            ret = core.playGame(name);
            showLib->createWindows();
         }
      }
   showLib->leave();
   showLib->close();
   // DLCLOSE QUELQUE PART
   close();
}

void
Menu::close()
{
   for (std::list<void *>::iterator it = sharedLibs.begin(); it != sharedLibs.end(); ++it)
      if (!dlclose(*it))
         return ;
}
