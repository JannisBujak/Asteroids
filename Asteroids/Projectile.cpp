#include "Projectile.h"
#include "Game.h"

Projectile::Projectile(sf::Vector2f a_position, float a_size, sf::Vector2f a_movement, Game* a_game, Moveable* m_shooter)
	: Moveable(a_game)
	, m_movement(a_movement)
{
	m_shape = std::make_shared<sf::CircleShape>(a_size);
	m_shape->setPosition(a_position);
}

void Projectile::move(float factor)
{
	sf::Vector2f factor_movement = factor * m_movement;

	moveShape(factor_movement);

	sf::FloatRect rect (m_shape->getPosition(), getSize());
	auto globbo = m_shape->getGlobalBounds();
	if (!rect.intersects(game()->getRect()))
	{
		game()->removeProjectile(this);
		std::cout << game()->num_elements() << " Elements remaining" << std::endl;
	}
}

const sf::Vector2f& Projectile::getSize() const
{
	auto circle = dynamic_cast<sf::CircleShape*>(m_shape.get());
	return sf::Vector2f(circle->getRadius(), circle->getRadius());
}
