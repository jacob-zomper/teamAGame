
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -L/usr/include/SDL2
CFLAGS = -I/usr/include/SDL2

PLAYER_CLASS = -c Player.cpp -o Player.o
MAPBLOCKS_CLASS = -c MapBlocks.cpp -o MapBlocks.o

INCLUDED_CLASSES = Player.o MapBlocks.o

all: SDLCredits.cpp game_loop.cpp
	g++ $(PLAYER_CLASS) $(LINKER_FLAGS)
	g++ $(MAPBLOCKS_CLASS) $(LINKER_FLAGS)
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp
	g++ -o game_loop $(LINKER_FLAGS) $(INCLUDED_CLASSES) game_loop.cpp

dilan: SDLCredits.cpp
	g++ $(PLAYER_CLASS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs)
	g++ $(MAPBLOCKS_CLASS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs)
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 -o game_loop.o

connor: SDLCredits.cpp game_loop.cpp
	g++ $(PLAYER_CLASS) $(LINKER_FLAGS) -std=c++11
	g++ $(MAPBLOCKS_CLASS) $(LINKER_FLAGS) -std=c++11
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits
	g++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -std=c++11 -o game_loop

kenneth: SDLCredits.cpp
	g++ $(PLAYER_CLASS) $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main
	g++ $(MAPBLOCKS_CLASS) $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main
	g++ $(INCLUDED_CLASSES) SDLCredits.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o SDLCredits

jerry_lin_game: game_loop.cpp
	clang++ $(PLAYER_CLASS) $(LINKER_FLAGS) $(CFLAGS)
	clang++ $(MAPBLOCKS_CLASS) $(LINKER_FLAGS) $(CFLAGS)
	clang++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) $(CFLAGS)  -o game

jerry_lin_enemy_test: enemy_test.cpp
	clang++ enemy_test.cpp $(LINKER_FLAGS) $(CFLAGS)  -o enemy_test

brandon: SDLCredits.cpp game_loop.cpp
	g++ $(PLAYER_CLASS) -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
	g++ $(MAPBLOCKS_CLASS) -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
	g++ SDLCredits.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o credits
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o game_loop
	g++ $(INCLUDED_CLASSES) test_enemy_move.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o test_enemy_move
	g++ enemy_test.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib   -o enemy_test



clean:
	rm *.o