#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Moveable
{
private:
	Game* m_game;

protected:
	std::shared_ptr<sf::Shape> m_shape;

public:
	Moveable(Game* a_game)		
		: m_game(a_game)
	{

	}
		
	virtual void move(float factor) = 0;

	virtual sf::Vector2f getCenter() const
	{
		return m_shape->getPosition();
	}

	virtual const sf::Vector2f& getPosition() const
	{
		return m_shape->getPosition();
	}

	virtual void setPosition(const sf::Vector2f& a_position)
	{
		m_shape->setPosition(a_position);
	}

	virtual const sf::Vector2f& getSize() const = 0;	


	virtual void setFillColor(sf::Color a_color)
	{
		m_shape->setFillColor(a_color);
	}

	const sf::Shape* shape() const
	{
		return m_shape.get();
	}

	virtual void moveShape(float x, float y)
	{
		m_shape->move(x, y);
	}

	virtual void moveShape(const sf::Vector2f& a_vector)
	{
		m_shape->move(a_vector);
	}

	Game* game()
	{
		return m_game;
	}
};
