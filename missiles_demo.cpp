// Using only public variables to make the demo easier

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

