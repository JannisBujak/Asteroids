#include "Moveable.h"

class Game;

class Projectile : public Moveable
{
private:	
	sf::Vector2f m_movement;

public:
	Projectile(sf::Vector2f a_position, sf::Vector2f a_size, sf::Vector2f a_movement, Game* a_game);


	virtual void move(float factor) override;
};