#include "Projectile.h"
#include "Game.h"

Projectile::Projectile(sf::Vector2f a_position, float a_size, uint64_t a_timeOfExistence, sf::Vector2f a_movement, Game* a_game, Moveable* m_shooter)
	: Moveable(a_game)
	, m_movement(a_movement)
	, m_creationTime(Millis())
	, m_timeOfExistence(a_timeOfExistence)
{
	m_shape = std::make_shared<sf::CircleShape>(a_size);
	m_shape->setPosition(a_position);
	m_shape->setOrigin(a_size/2, a_size/2);
}

void Projectile::move(float factor)
{
	// Überprüfen, ob Projectile noch existiert 
	/*
	sf::FloatRect rect(m_shape->getPosition(), getSize());
	auto globbo = m_shape->getGlobalBounds();
	if (!rect.intersects(game()->getRect()))
	{
		game()->removeMoveable(this);
		std::cout << game()->num_elements() << " Elements remaining" << std::endl;
	}
	*/	
	if (Millis() - m_creationTime > m_timeOfExistence)
	{
		game()->removeMoveable(this);
		std::cout << game()->num_elements() << " Elements remaining" << std::endl;
	}
	// Sonst normal update 
	
	sf::Vector2f factor_movement = factor * m_movement;

	moveShape(factor_movement);

}

const sf::Vector2f& Projectile::getSize() const
{
	auto circle = dynamic_cast<sf::CircleShape*>(m_shape.get());
	return sf::Vector2f(circle->getRadius(), circle->getRadius());
}
