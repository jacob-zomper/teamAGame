AI Brainstrom:



Goals:
	
	* Rockets that track player
		* could be a special type of "bullet"
		* or could be a special type of "enemy"

	* Planes that can shoot enemy player, or dodge them

	* AI dodges incoming fire from player

"Classes":
	
	* Enemy Class
		* more like an interface probably. header file
		* defines enemy functionality such as:
			* detect player
			* detect incoming fire
			* "dodge"
			* "shoot"
			* movement

	* Subclasses of Enemy
		* must define specific enemy characteristics such as:
			* the enemy sprite
			* the hitbox
			* define the functions from Enemy
				* movement, shooting, or dodging might be different for different enemy types
				* 
		* Rocket would probably be one of these