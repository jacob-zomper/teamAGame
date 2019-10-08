
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -L/usr/include/SDL2
CFLAGS = -I/usr/include/SDL2

INCLUDED_CLASSES = Player.cpp MapBlocks.cpp GameOver.cpp

all: SDLCredits.cpp game_loop.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -o game_loop $(LINKER_FLAGS)

dilan: SDLCredits.cpp
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 -o game_loop.o

connor: SDLCredits.cpp game_loop.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits
	g++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -std=c++11 -o game_loop

kenneth: SDLCredits.cpp
	g++ $(INCLUDED_CLASSES) SDLCredits.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o SDLCredits

jerry_lin_game: game_loop.cpp
	clang++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) $(CFLAGS)  -o game

jerry_lin_enemy_test: enemy_test.cpp
	clang++ enemy_test.cpp $(LINKER_FLAGS) $(CFLAGS)  -o enemy_test

brandon: SDLCredits.cpp game_loop.cpp
	g++ SDLCredits.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o credits
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o game_loop
	g++ enemy_test.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib   -o enemy_test

brandon_enemy: test_enemy_move.cpp
	g++ -c brandon_enemy.cpp -o brandon_enemy.o -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
	g++ $(INCLUDED_CLASSES) brandon_enemy.o test_enemy_move.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o test_enemy_move


jake: SDLCredits.cpp game_loop.cpp 
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 -o game_loop

cleanjake:
	rm game_loop

clean:
	rm *.o