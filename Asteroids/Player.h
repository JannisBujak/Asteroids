#pragma once

// #include <SFML/Graphics.hpp>

#include "Moveable.h"

#include "KeyboardReader.h"

#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

class Weapon;

class Player
	: public Moveable
{
private:
	float movement_speed;
	
	sf::Vector2f m_moveSpeed;
	inline static const float TURN_SPEED = 100;
	inline static const float FRICTION = 0.8;
	inline static const double ACCELERATION = 2000;


	std::shared_ptr<Weapon> m_weapon;
public:
	

public:
	Player(float width, float height, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game);
	Player(const sf::Vector2f& size, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game);

	sf::Vector2f PlayerDirection() const;

	virtual sf::Vector2f getCenter() const override;

	virtual const sf::Vector2f& getSize() const override;	

public:
	static float horiz_vert_movement_from_diagonal(float c);

public:
	static float angleDegIntoRed(float angle);
	void handleInputs(std::vector<KeyboardReader::Command> given_directions, float factor);
	void moveByDirections(std::vector<KeyboardReader::Command> given_directions, float factor);
	
	// factor depends on delta-time and the KeyTargetTime
	virtual void move(float factor) override;

	virtual QJsonObject toJson() const override;
};

