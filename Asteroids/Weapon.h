
// #include "Projectile.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Game;
class Moveable;
class Projectile;

class Weapon
{
protected:
	int64_t last_shot_ms;
public:
	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game, Moveable* m_shooter) = 0;
};

class Gun1 : public Weapon
{
	const static int64_t COOLDOWN_MS = 300;
	inline const static int64_t BULLET_MOVEMENT_SPEED = 1000;
public:
	Gun1() = default;

	virtual std::shared_ptr<Projectile> produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game, Moveable* m_shooter) override;
};
