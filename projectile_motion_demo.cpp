#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

const int M_PI = atan(1) * 4;
const int radian_to_degree = 180.0 / M_PI;

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
			return velocity * cos(pitch * radian_to_degree);
		}

		// Decreases the y velocity by the air time to simulate bullet drop
		// May have to experience with the divisor
		int y_velocity()
		{
			return velocity * sin(pitch * radian_to_degree) - (air_time / 3);
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

		int get_air_time()
		{
			return air_time;
		}

	private:
		// x and y coordinates, magnitude of velocity, and time the projectile has been in the air (starts at 0)
		int x_position, y_position, velocity, pitch, air_time;
};

void output_info(Projectile* projectile)
{
	std::cout << "(" << projectile->get_x_position() << ", " << projectile->get_y_position() << ")";
	std::cout << " - " << projectile->x_velocity() << "/" << projectile->y_velocity();
	std::cout << " [" << projectile->get_air_time() << "]" << std::endl;
}

void wait_milliseconds(int amount)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(amount));
}

int main()
{
	int x_position = 0, y_position = 0, velocity = 5, pitch = 220;
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