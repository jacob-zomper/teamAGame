LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(TARGET)

$(TARGET):
	g++ -o SDLCredits $(LINKER_FLAGS) SDLCredits.cpp

clean:
	rm $(TARGET)
