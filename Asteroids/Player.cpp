#include "Player.h"


Player::Player(float width, float height, float movement_speed)
	: Moveable(sf::Vector2f(width, height)), movement_speed(movement_speed)
{
}

Player::Player(const sf::Vector2f& size, float movement_speed)
	: Moveable(size), movement_speed(movement_speed)
{
}

void Player::setMovementSpeed(float movement_speed)
{
	this->movement_speed = movement_speed;
}

float Player::getMovementSpeed() const
{
	return movement_speed;
}

float Player::horiz_vert_movement_from_diagonal(float c)
{
	return c / sqrt(2);
}

void Player::moveByDirections(std::vector<KeyboardReader::Direction> given_directions, float factor)
{
	float vert_horiz_speed = factor * movement_speed;
	if (given_directions.empty())
		return;
	else if (given_directions.size() > 2)
	{
		std::string error_msg = "Wrong number of arguments, having " + std::to_string(given_directions.size()) + " directions given";
		throw std::exception(error_msg.c_str());
	}
	else if (given_directions.size() == 2)
		vert_horiz_speed = horiz_vert_movement_from_diagonal(vert_horiz_speed);

	float horiz = 0, vert = 0;
	for (KeyboardReader::Direction& dir : given_directions)
	{
		switch (dir)
		{
		case KeyboardReader::Direction::Up:
			vert -= vert_horiz_speed;
			break;
		case KeyboardReader::Direction::Right:
			horiz += vert_horiz_speed;
			break;
		case KeyboardReader::Direction::Down:
			vert += vert_horiz_speed;
			break;
		case KeyboardReader::Direction::Left:
			horiz -= vert_horiz_speed;
			break;
		}
	}
	((sf::RectangleShape*)this)->move(horiz, vert);
}

void Player::move(float factor)
{
	//std::vector<KeyboardReader::Direction> directions = getDirectionRemoveDuplicates(pressed_keys);
	std::vector<KeyboardReader::Direction> directions = KeyboardReader::getDirections();
	if (directions.empty())
		return;
	moveByDirections(directions, factor);
}

