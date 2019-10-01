LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: SDLCredits.cpp
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp

dilan: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) $$(sdl2-config --cflags --libs) -std=c++11 -o SDLCredits.o

connor: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -std=c++11 -o SDLCredits

kenneth: SDLCredits.cpp
	g++ SDLCredits.cpp $(LINKER_FLAGS) -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -o SDLCredits

clean:
	rm SDLCredits.o
