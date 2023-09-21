
// #include "Projectile.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Game;
class Projectile;

class Weapon
{
protected:
	int64_t last_shot_ms;
public:
	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game) = 0;
};

class Gun1 : public Weapon
{
	const static int64_t cooldown_ms = 300;
	inline const static int64_t gun_movement_speed = 300;
public:
	Gun1() = default;

	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game) override;
};
