#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Moveable : public sf::RectangleShape
{
private:
	Game* m_game;
public:
	Moveable(sf::Vector2f size, Game* a_game)
		: sf::RectangleShape(size)
		, m_game(a_game)
	{

	}

	virtual void move(float factor) = 0;
	
	Game* game()
	{
		return m_game;
	}
};
