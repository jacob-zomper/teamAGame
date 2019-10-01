
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -L/usr/include/SDL2
CFLAGS = -I/usr/include/SDL2

all: SDLCredits.cpp
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp

dilan: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) $$(sdl2-config --cflags --libs) -std=c++11 -o SDLCredits

connor: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits

kenneth: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o SDLCredits

jerry_lin_game: game_loop.cpp
	clang++ game_loop.cpp $(LINKER_FLAGS) $(CFLAGS)  -o game

jerry_lin_enemy_test: enemy_test.cpp
	clang++ enemy_test.cpp $(LINKER_FLAGS) $(CFLAGS)  -o enemy_test

clean:
	rm SDLCredits.o