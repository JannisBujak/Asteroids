
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
	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f pos, Game* game) = 0;
};

class Gun1 : public Weapon
{
	const static int64_t cooldown_ms = 300;
public:
	Gun1() = default;

	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f a_pos, Game* game) override;
};
