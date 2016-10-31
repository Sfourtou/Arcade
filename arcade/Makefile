MACHINE= $(shell uname -s)

NAME = arcade

SRC_EXE = sources/main.cpp \
	sources/Menu.cpp  \
	sources/Core.cpp \
	sources/AGame.cpp \
	sources/Map.cpp \
	sources/Utils.cpp \
	sources/Score.cpp

SRC_CENTIPEDE = sources/AGame.cpp \
	sources/Utils.cpp \
	sources/Map.cpp \
	sources/ACharacter.cpp \
	sources/Score.cpp \
	sources/Timer.cpp \
	sources/Centipede.cpp \
	sources/Ship.cpp \
	sources/Mushroom.cpp \
	sources/Shoot.cpp \
	sources/CentipedeEntity.cpp \
	sources/CentipedeBody.cpp


SRC_NIBBLER = sources/AGame.cpp \
	sources/Utils.cpp \
	sources/Map.cpp \
	sources/ACharacter.cpp \
	sources/Score.cpp \
	sources/Nibbler.cpp \
	sources/SnakeEntity.cpp \
	sources/SnakeBody.cpp \
	sources/Fruit.cpp \
	sources/Timer.cpp

SRC_PACMAN = sources/AGame.cpp \
	sources/Utils.cpp \
	sources/Map.cpp \
	sources/ACharacter.cpp \
	sources/Score.cpp \
	sources/PacMan.cpp \
	sources/PacmanEntity.cpp \
	sources/Ghost.cpp \
	sources/Timer.cpp

OBJ_EXE = $(SRC_EXE:.cpp=.o)

OBJ_NIBBLER = $(SRC_NIBBLER:.cpp=.o)

OBJ_PACMAN = $(SRC_PACMAN:.cpp=.o)

OBJ_CENTIPEDE = $(SRC_CENTIPEDE:.cpp=.o)

SRC_LIB = sources/Sfml.cpp \
	sources/TileMap.cpp \
	sources/Sprite.cpp

SRC_CURSES = sources/Ncurses.cpp

SRC_OPENGL = sources/Opengl.cpp

OBJ_LIB = $(SRC_LIB:.cpp=.o)
OBJ_CURSES = $(SRC_CURSES:.cpp=.o)
OBJ_OPENGL = $(SRC_OPENGL:.cpp=.o)

NAME_SFML = ./lib/lib_arcade_sfml.so
NAME_CURSES = ./lib/lib_arcade_ncurses.so
NAME_OPENGL = ./lib/lib_arcade_opengl.so
NAME_NIBBLER = ./games/lib_arcade_nibbler.so
NAME_PACMAN = ./games/lib_arcade_pacman.so
NAME_CENTIPEDE = ./games/lib_arcade_centipede.so

SFML_FLAGS += -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lncurses
CURSES_FLAGS += -lncurses
ifeq ($(MACHINE), Darwin)
 OPENGL_FLAGS += -framework GLUT -framework OpenGL -lSDL_image -lm -lSDL -lSDL_ttf 
else
 OPENGL_FLAGS += -lSDL -lGLU -lglut -lGL -lSDL_image -lSDL_ttf -lm
endif
LDFLAGS += -ldl
CXXFLAGS += -I./includes -fPIC -std=c++11 -w  -Wno-deprecated-declaration

CXX = g++

all:  $(NAME_NIBBLER) $(NAME_PACMAN) $(NAME_CENTIPEDE)

lib:  $(NAME_CURSES) $(NAME_SFML) $(NAME_OPENGL)

everything: all lib arc

arc: $(NAME)

$(NAME_SFML): 	$(OBJ_LIB)
	$(CXX) -shared -o $(NAME_SFML) $(OBJ_LIB) $(SFML_FLAGS)

$(NAME_CURSES): $(OBJ_CURSES)
	$(CXX) -shared -o $(NAME_CURSES) $(OBJ_CURSES) $(CURSES_FLAGS)

$(NAME_OPENGL): $(OBJ_OPENGL)
		$(CXX) -shared -o $(NAME_OPENGL) $(OBJ_OPENGL) $(OPENGL_FLAGS)

$(NAME_NIBBLER): $(OBJ_NIBBLER)
		$(CXX) -shared -o $(NAME_NIBBLER) $(OBJ_NIBBLER)

$(NAME_PACMAN): $(OBJ_PACMAN)
		$(CXX) -shared -o $(NAME_PACMAN) $(OBJ_PACMAN)

$(NAME_CENTIPEDE): $(OBJ_CENTIPEDE)
		$(CXX) -shared -o $(NAME_CENTIPEDE) $(OBJ_CENTIPEDE)

$(NAME):	$(OBJ_EXE)
	$(CXX) -o $(NAME) $(OBJ_EXE) $(LDFLAGS) -lm

clean:
	rm -f $(OBJ_LIB)
	rm -f $(OBJ_EXE)
	rm -f $(OBJ_CURSES)
	rm -f $(OBJ_OPENGL)
	rm -f $(OBJ_NIBBLER)
	rm -f $(OBJ_PACMAN)
	rm -f $(OBJ_CENTIPEDE)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_SFML)
	rm -f $(NAME_CURSES)
	rm -f $(NAME_OPENGL)
	rm -f $(NAME_PACMAN)
	rm -f $(NAME_NIBBLER)
	rm -f $(NAME_CENTIPEDE)

re: fclean all

.PHONY: all everything lib clean fclean re
