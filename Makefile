
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -I/usr/include/sdl

all: SDLCredits.cpp game_loop.cpp
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp
	g++ -o game_loop $(LINKER_FLAGS) game_loop.cpp

dilan: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) $$(sdl2-config --cflags --libs) -std=c++11 -o SDLCredits

connor: SDLCredits.cpp game_loop.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits
	g++ game_loop.cpp $(LINKER_FLAGS) -std=c++11 -o game_loop

kenneth: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o SDLCredits

jerry_lin_game: game_loop.cpp
	clang++ game_loop.cpp -L/usr/include/SDL2 $(LINKER_FLAGS) $(CFLAGS)  -o game

jerry_lin_enemy_test: enemy_test.cpp
	clang++ enemy_test.cpp -L/usr/include/SDL2 $(LINKER_FLAGS) $(CFLAGS)  -o enemy_test

clean:
	rm SDLCredits.o