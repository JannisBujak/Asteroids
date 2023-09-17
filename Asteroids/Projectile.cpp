#include "Projectile.h"
#include "Game.h"

Projectile::Projectile(sf::Vector2f a_position, sf::Vector2f a_size, sf::Vector2f a_movement, Game* a_game)
	: Moveable(a_size, a_game)
	, m_movement(a_movement)
{
	this->setPosition(a_position);
}

void Projectile::move(float factor)
{
	sf::Vector2f factor_movement = factor * m_movement;

	((sf::RectangleShape*)this)->move(factor_movement);

	sf::FloatRect rect (getPosition(), getSize());
	if (!rect.intersects(game()->getRect()))
	{
		game()->removeProjectile(this);
		std::cout << game()->num_elements() << " Elements remaining" << std::endl;
	}

}
