CPP_FILE = $(SDLCredits.cpp)
OUT_NAMES = $(patsubst %.cpp,%.o,$(CPP_FILE))
CC = clang++
COMPILER_FLAGS = -Wall -I/usr/include/SDL2
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(OUT_NAMES)

%.o: %.cpp
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

clean:
	rm *.o
