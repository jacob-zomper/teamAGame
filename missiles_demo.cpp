// Using only public variables to make the demo easier

#include <chrono>
#include <thread>

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

// Conversion constant
const double degree_to_radian = atan(1) * 4 / 180.0;

class Plane
{
	public:
		Plane(double hit_points, double x_position, double y_position,
			double x_velocity, double y_velocity, double direction) :
			hit_points{ hit_points }, x_position{ x_position }, y_position{ y_position },
			x_velocity{ x_velocity }, y_velocity{ y_velocity }, direction{ direction } {}

		// Amount of damage the plane can endure before it is destroyed
		double hit_points;

		// Position coordinates
		double x_position, y_position;

		// Velocity components
		double x_velocity, y_velocity;

		// Direction angle in degrees
		double direction;

		// Deals damage to the plane's hitpoints
		double deal_damage(double damage)
		{
			if (damage >= hit_points)
			{
				hit_points = 0;
			}
			else
			{
				hit_points -= damage;
			}
		}

		void move()
		{
			x_position += x_velocity * cos(direction * degree_to_radian);
			y_position += y_velocity * sin(direction * degree_to_radian);
		}
};

class Missile
{
	public:
		Missile(double damage, double x_position, double y_position,
			double x_velocity, double y_velocity, double direction, double blast_radius) :
			damage{ damage }, x_position{ x_position }, y_position{ y_position },
			x_velocity{ x_velocity }, y_velocity{ y_velocity }, direction{ direction },
			blast_radius{ blast_radius } {}

		// Amount of damage the warhead deals at the center of the blast radius
		double damage;

		// Position coordinates
		double x_position, y_position;

		// Velocity components
		double x_velocity, y_velocity;

		// Direction angle in degrees
		double direction;

		// Maximum distance the warhead can cause damage
		double blast_radius;

		// Calculates how far the entity is to this missile,
		// using the basic distance formula for two points in a X and Y plane
		double calculate_distance(int entity_x, int entity_y)
		{
			return abs(sqrt(pow(x_position - entity_x, 2) + pow(y_position - entity_y, 2)));
		}

		// Calculates how much damage the warhead will do to entity,
		// depending on the entity's distance to the warhead
		// Using a very simple rational function for now
		double calculate_damage(int entity_x, int entity_y)
		{
			double distance = calculate_distance(entity_x, entity_y);

			return damage / distance;
		}

		void move()
		{
			x_position += x_velocity * cos(direction * degree_to_radian);
			y_position += y_velocity * sin(direction * degree_to_radian);
		}
};

// Vector that stores all planes in the game
vector<Plane*> planes;

// Deals damage to all planes that are within the blast radius of the missile
void check_blast(Missile* missile)
{
	vector<Plane*> affected_planes;

	for (auto& plane : planes)
	{
		double distance = missile->calculate_distance(plane->x_position, plane->y_position);

		if (distance <= missile->blast_radius)
		{
			double damage = missile->calculate_damage(plane->x_position, plane->y_position);
			plane->deal_damage(damage);
		}
	}
}

// Waits for passed number of nanoseconds
void wait(int time)
{
	this_thread::sleep_for(chrono::milliseconds(time));
}

int main()
{
	// Hit points, starting x and y position, starting x and y velocity, and velocity direction
	Plane* plane1 = new Plane(100, 10, 0, 0, 0, 0);
	Plane* plane2 = new Plane(100, 11, 0, 0, 0, 0);

	planes.push_back(plane1);
	planes.push_back(plane2);

	// Damage, starting x and y position, starting x and y velocity, velocity direction, and blast radius
	Missile* missile1 = new Missile(100, 0, 0, 0, 0, 0, 10);

	cout << "Before missile blast:" << endl;

	for (auto plane : planes)
	{
		cout << "Plane hitpoints: " << plane->hit_points << endl;
	}

	check_blast(missile1);

	cout << "After missile blast:" << endl;

	for (auto plane : planes)
	{
		cout << "Plane hitpoints: " << plane->hit_points << endl;
	}

	bool gameon = true;
	while (gameon)
	{
		for (auto& plane : planes)
		{
			plane->move();
			cout << "Plane x: " << plane->x_position << " y: " << plane->y_position << endl;
		}


		wait(750);
	}

	delete(plane1);
	delete(plane2);
	delete(missile1);
}