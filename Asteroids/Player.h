#pragma once

// #include <SFML/Graphics.hpp>

#include "Moveable.h"

#include "KeyboardReader.h"

#include <iostream>
#include <algorithm>


class Player
	: public Moveable
{
private:
	float movement_speed;
public:
	

public:
	Player(float width, float height, float movement_speed = 0);
	Player(const sf::Vector2f& size, float movement_speed = 0);


	void setMovementSpeed(float movement_speed);
	float getMovementSpeed() const;


public:
	static float horiz_vert_movement_from_diagonal(float c);

public:
	void moveByDirections(std::vector<KeyboardReader::Direction> given_directions, float factor);
	
	// factor depends on delta-time and the KeyTargetTime
	void move(float factor);
};

