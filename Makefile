LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: SDLCredits.cpp
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp

clean:
	rm SDLCredits.o
