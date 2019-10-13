#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <SDL.h>

// Global variables
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int PLANE_WIDTH = 40;
constexpr int PLANE_HEIGHT = 40;
constexpr int MAX_SPEED = 5;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

// Function declarations
bool init();
void close();

bool init() 
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    gWindow = SDL_CreateWindow(
        "Hello world!", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN);

    if(gWindow == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Add Vsync to limit framerate
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(gRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set renderer draw/clear color
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

    return true;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    SDL_Quit();
}

class Plane
{
    public:
        Plane(double xp, double yp, int v, int p) :x_position{xp}, y_position{yp}, velocity{v}, pitch{p} {}

        // Updates the x and y positions based on current velocity and pitch
        void update_position()
        {
            x_position += get_x_velocity();
            y_position += get_y_velocity();
        }

        // The following two functions calculate the X and Y velocities based on trigonometry

        double get_x_velocity()
        {
            return velocity * cos(pitch * M_PI / 180.0);
        }

        double get_y_velocity()
        {
            return velocity * sin(pitch * M_PI / 180.0);
        }

        // Sets coordinates, velocity, and pitch to starting values
        void reset()
        {
            set_position(0, SCREEN_HEIGHT / 2);
            velocity = 0;
            pitch = 0;
        }

        // Returns true if object is at or passed a screen boundary, false otherwise
        bool at_boundary()
        {
            if(x_position >= SCREEN_WIDTH || x_position < 0 || y_position >= SCREEN_HEIGHT || y_position < 0)
            {
                return true;
            }
            else
            {
                return false;
            }            
        }

        // Returns true if object is at or passed the maximum speed, false otherwise
        bool at_max_speed()
        {
            if(abs(velocity) >= MAX_SPEED)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // Incrementers and decrementers for velocity and pitch

        void add_velocity(int value)
        {
            if(!at_max_speed)
            {
                velocity += value;
            }
        }

        void add_pitch(int value)
        {
            pitch += value;
        }

        // Setter methods for position, velocity, and pitch

        void set_position(int x, int y)
        {
            x_position = x;
            y_position = y;
        }

        void set_velocity(int v)
        {
            velocity = v;
        }

        void set_pitch(int p)
        {
            pitch = p;
        }

        // Getter methods for position and pitch

        double get_x_position()
        {
            return x_position;
        }

        double get_y_position()
        {
            return y_position;
        }

        int get_pitch()
        {
            return pitch;
        }

    private:
        // Position within screen in pixels
        double x_position, y_position;

        // Velocity in pixels per game loop
        int velocity;

        // Nose pitch in degrees
        int pitch;
};

int main()
{
    if(!init())
    {
        std::cout << "Failed to initalize!" << std::endl;
        close();
        return 1;
    }

    // Create plane object with 0 velocity and pitch,
    // placed in the middle of the left start of the screen
    Plane plane(0, SCREEN_HEIGHT / 2, 0, 0);

    SDL_Event e;
    bool gameon = true;
    while(gameon)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gameon = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_w:
                        plane.add_pitch(-5);
                        break;
                    case SDLK_a:
                        plane.add_velocity(-1);
                        break;
                    case SDLK_s:
                        plane.add_pitch(5);
                        break;
                    case SDLK_d:
                        plane.add_velocity(1);
                        break;
                }
            }
        }

        if(plane.at_boundary())
        {
            plane.reset();
        }

        plane.update_position();

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_Rect fillRect = {(int) plane.get_x_position(), (int) plane.get_y_position(), PLANE_WIDTH, PLANE_HEIGHT};
        SDL_RenderFillRect(gRenderer, &fillRect);
        SDL_RenderPresent(gRenderer);

        std::cout << "Pitch: " << plane.get_pitch() << " Velocity: " << plane.get_x_velocity() << "/" << plane.get_y_velocity() << std::endl;
    }

    close();
    return 1;
}