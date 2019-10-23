#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

// Math constants
const int M_PI = atan(1) * 4;
const int radian_to_degree = 180.0 / M_PI;

// Increase value to have projectile fall slower and have less air resistance (drag)
// Decrease to have projectile fall faster and have more air resistance
const int air_time_divisor = 3;

class Projectile {
	public:
		Projectile(int xp, int yp, int v, int p) :x_position{ xp }, y_position{ yp }, velocity{ v }, pitch{ p }, air_time{ 0 } {}

		void update_position()
		{
			x_position += x_velocity();
			y_position += y_velocity();
			air_time++;
		}

		int x_velocity()
		{
			// Decrease x velocity to simulate air resistance,
			// but half as slowly as the decrease in y velocity
			int adjustment = air_time / (2 * air_time_divisor);
			int x_velocity = velocity * cos(pitch * radian_to_degree);

			// Prevent projectile from moving backwards in the x-direction
			int adjusted_x_velocity = x_velocity - adjustment;
			if (adjusted_x_velocity <= 0)
			{
				adjusted_x_velocity = 0;
			}

			return adjusted_x_velocity;
		}

		int y_velocity()
		{
			// Decreases the y velocity by the air time to simulate bullet drop
			int adjustment = air_time / air_time_divisor;
			int y_velocity = velocity * sin(pitch * radian_to_degree);

			return y_velocity - adjustment;
		}

		// Accessor methods
		int get_x_position()
		{
			return x_position;
		}

		int get_y_position()
		{
			return y_position;
		}

		int get_pitch()
		{
			return pitch;
		}

	private:
		// x and y coordinates, magnitude of velocity, and time the projectile has been in the air (starts at 0)
		int x_position, y_position, velocity, pitch, air_time;
};

void output_info(Projectile* projectile)
{
	std::cout << "(" << projectile->get_x_position() << ", " << projectile->get_y_position() << ")";
	std::cout << " - " << projectile->x_velocity() << "/" << projectile->y_velocity();
	std::cout << " [" << projectile->get_pitch() << "]" << std::endl;
}

void wait_milliseconds(int amount)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(amount));
}

int main()
{
	int x_position = 0, y_position = 0, velocity = 5, pitch = 0;
	Projectile* projectile = new Projectile(x_position, y_position, velocity, pitch);

	std::cout << "( x position, y position) - x velocity / y velocity [ pitch ]" << std::endl;

	bool gameon = true;
	while (gameon)
	{
		projectile->update_position();
		output_info(projectile);
		wait_milliseconds(750);
	}

	delete(projectile);
}