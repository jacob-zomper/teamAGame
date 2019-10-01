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
			* "death" function for when the plane collides with an object or is shot

	* Subclasses of Enemy
		* must define specific enemy characteristics such as:
			* the enemy sprite
			* the hitbox
			* define the functions from Enemy
				* movement, shooting, or dodging might be different for different enemy types
					* Possible method of decision-making - have enemy predict the future by "running" a few seconds of gameplay, and selecting moves that are likely to result in the player's death
					* Possible method of decision-making - some type of enemy cooperation, i.e. enemies fire at the same time as each other to maximize chance of hitting player
					* Could have "kamikaze" planes that fly close to the player and ranged planes that stay farther away
					* Possible method of decision-making - have enemies be aware of each other and use this to fly in more complex patterns after the enemy in open air
		* Rocket would probably be one of these
