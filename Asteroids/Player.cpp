#include "Player.h"
#include "Projectile.h"
#include "Game.h"
#include "Weapon.h"


Player::Player(float width, float height, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game)
	: Moveable(sf::Vector2f(width, height), a_game)
	, movement_speed(movement_speed)
	, m_weapon(a_weapon)
{
}

Player::Player(const sf::Vector2f& size, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game)
	: Moveable(size, a_game)
	, movement_speed(movement_speed)
	, m_weapon(a_weapon)
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

sf::Vector2f Player::getCenter() const
{
	sf::Vector2f size = getSize();
	return getPosition() + sf::Vector2f(0.5*size.x, 0.5*size.y);
}

float Player::horiz_vert_movement_from_diagonal(float c)
{
	return c / sqrt(2);
}

void Player::moveByDirections(std::vector<KeyboardReader::Command> given_directions, float factor)
{
	float vert_horiz_speed = factor * movement_speed;
	if (given_directions.empty())
		return;

	float horiz = 0, vert = 0;
	for (KeyboardReader::Command& dir : given_directions)
	{
		switch (dir)
		{
		case KeyboardReader::Command::Up:
			vert -= vert_horiz_speed;
			break;
		case KeyboardReader::Command::Right:
			horiz += vert_horiz_speed;
			break;
		case KeyboardReader::Command::Down:
			vert += vert_horiz_speed;
			break;
		case KeyboardReader::Command::Left:
			horiz -= vert_horiz_speed;
			break;
		case KeyboardReader::Command::Shoot:
			if (m_weapon)
			{
				auto proj = m_weapon->produceProjectile(getCenter(), game());
				if (proj)
					game()->addProjectile(proj);
			}
				
		}
	}
	if (horiz != 0 && vert != 0)
	{
		vert /= sqrt(2);
		horiz /= sqrt(2);
	}
	((sf::RectangleShape*)this)->move(horiz, vert);
}

void Player::move(float factor)
{
	//std::vector<KeyboardReader::Direction> directions = getDirectionRemoveDuplicates(pressed_keys);
	std::vector<KeyboardReader::Command> directions = KeyboardReader::getDirections();
	if (directions.empty())
		return;
	moveByDirections(directions, factor);
}

