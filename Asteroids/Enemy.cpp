

#include "Enemy.h"
#include "Game.h"

ShootingEnemy::ShootingEnemy(Game* a_game)
	: Moveable(a_game)
{	
}

const sf::Vector2f& ShootingEnemy::getSize() const
{
	auto circle = dynamic_cast<sf::CircleShape*>(m_shape.get());
	return sf::Vector2f(circle->getRadius(), circle->getRadius());
}

Turret1::Turret1(sf::Vector2f a_pos, Game* a_game)
	: ShootingEnemy(a_game)
{
	m_weapon = std::make_shared<TurretGun1>();
	m_shape = std::make_shared<sf::CircleShape>(TURRET_RADIUS);
	m_shape->setOrigin(TURRET_RADIUS / 2, TURRET_RADIUS / 2);
	m_shape->setPosition(a_pos);
	m_shape->setFillColor(sf::Color::Red);
}

std::shared_ptr<Weapon> Turret1::getWeapon() const
{
	return m_weapon;
}

float Turret1::getRange() const
{
	return TURRET_RANGE;
}

void Turret1::move(float factor)
{
	auto player_pos = game()->getPlayer()->getCenter();
	if (player_pos != getCenter())
	{
		float distance = PointDistance(getCenter(), game()->getPlayer()->getCenter());
		if (distance < getRange() && m_weapon)
		{
			auto proj = m_weapon->produceProjectile(getCenter(), player_pos - getCenter(), game(), this);
			if (proj)
				game()->addProjectile(proj);
		}
	}
}
