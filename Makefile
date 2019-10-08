
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -I/usr/include/SDL2

PLAYER_CLASS = -c Player.cpp -o Player.o
MAPBLOCKS_CLASS = -c MapBlocks.cpp -o MapBlocks.o
BULLET_CLASS = -c bullet.cpp -o bullet.o
ENEMY_CLASS = -c enemy.cpp -o enemy.o
GAMEOVER_CLASS = -c GameOver.cpp -o GameOver.o

INCLUDED_CLASSES = Player.o MapBlocks.o bullet.o enemy.o GameOver.o

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
	clang++ $(LINKER_FLAGS) $(PLAYER_CLASS) 
	clang++ $(LINKER_FLAGS) $(MAPBLOCKS_CLASS) 
	clang++ $(LINKER_FLAGS) $(BULLET_CLASS)
	clang++ $(LINKER_FLAGS) $(ENEMY_CLASS)
	clang++ $(LINKER_FLAGS) $(GAMEOVER_CLASS)
	clang++ $(INCLUDED_CLASSES) game_loop.cpp $(LINKER_FLAGS) -o game


jerry_lin_enemy_test: test_enemy_move.cpp
	clang++ $(LINKER_FLAGS) $(PLAYER_CLASS) 
	clang++ $(LINKER_FLAGS) $(MAPBLOCKS_CLASS) 
	clang++ $(LINKER_FLAGS) $(BULLET_CLASS)
	clang++ $(LINKER_FLAGS) $(ENEMY_CLASS)
	clang++ $(LINKER_FLAGS) $(GAMEOVER_CLASS)
	clang++ $(INCLUDED_CLASSES) test_enemy_move.cpp $(LINKER_FLAGS)  -o enemy_test

brandon: SDLCredits.cpp game_loop.cpp
	g++ SDLCredits.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o credits
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o game_loop
	g++ $(INCLUDED_CLASSES) test_enemy_move.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o test_enemy_move
	g++ enemy_test.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib   -o enemy_test

brandon_enemy: test_enemy_move.cpp
	g++ -c brandon_enemy.cpp -o brandon_enemy.o -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib
	g++ $(INCLUDED_CLASSES) brandon_enemy.o test_enemy_move.cpp -lSDL2 -lSDL2_image -lmingw32 -lSDL2main -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -o test_enemy_move

jake: SDLCredits.cpp game_loop.cpp 
	g++ $(LINKER_FLAGS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 $(PLAYER_CLASS) 
	g++ $(LINKER_FLAGS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 $(MAPBLOCKS_CLASS) 
	g++ $(LINKER_FLAGS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 $(BULLET_CLASS)
	g++ $(LINKER_FLAGS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 $(ENEMY_CLASS)
	g++ $(LINKER_FLAGS) -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 $(GAMEOVER_CLASS)
	g++ $(INCLUDED_CLASSES) game_loop.cpp -lSDL2_image -lSDL2_ttf $$(sdl2-config --cflags --libs) -std=c++11 -o game_loop

cleanjake:
	rm game_loop
	rm *.o

clean:
	rm *.o