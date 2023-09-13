#pragma once

#include <SFML/Graphics.hpp>

class Moveable : public sf::RectangleShape
{
public:
	Moveable(sf::Vector2f size)
		: sf::RectangleShape(size)
	{

	}

	virtual void move(float factor) = 0;
};
