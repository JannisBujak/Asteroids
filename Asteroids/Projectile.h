#pragma once

#include "Moveable.h"

class Game;

class Projectile : public Moveable
{
private:	
	sf::Vector2f m_movement;
	Moveable* m_shooter;
	const uint64_t m_creationTime, m_timeOfExistence;
public:
	Projectile(sf::Vector2f a_position, float a_size, uint64_t a_timeOfExistence, sf::Vector2f a_movement, Game* a_game, Moveable* m_shooter);

	virtual void move(float factor) override;

	virtual const sf::Vector2f& getSize() const override;
};