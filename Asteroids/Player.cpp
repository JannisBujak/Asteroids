#include "Player.h"
#include "Projectile.h"
#include "Game.h"
#include "Weapon.h"


Player::Player(float width, float height, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game)
	: Moveable(a_game)
	, movement_speed(movement_speed)
	, m_weapon(a_weapon)
{
	m_shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));	
	m_shape->setOrigin(width / 2, height / 2);
}

Player::Player(const sf::Vector2f& size, float movement_speed, std::shared_ptr<Weapon> a_weapon, Game* a_game)
	: Moveable(a_game)
	, movement_speed(movement_speed)
	, m_weapon(a_weapon)
{
	m_shape = std::make_shared<sf::RectangleShape>(size);			
	m_shape->setOrigin(size.x/2, size.y/2);
}

sf::Vector2f Player::PlayerDirection() const
{
	auto rectshape = dynamic_cast<sf::RectangleShape*>(m_shape.get());
	float rotation = rectshape->getRotation();
	return sf::Vector2f(cos(angleDegIntoRed(rotation)), sin(angleDegIntoRed(rotation)));
}

sf::Vector2f Player::getCenter() const
{
	return getPosition();
}

const sf::Vector2f& Player::getSize() const
{
	return dynamic_cast<sf::RectangleShape*>(m_shape.get())->getSize();
}

float Player::horiz_vert_movement_from_diagonal(float c)
{
	return c / sqrt(2);
}

float Player::angleDegIntoRed(float angle)
{
	return angle * M_PI/ 180;
}

void Player::handleInputs(std::vector<KeyboardReader::Command> given_directions, float factor)
{
	static bool acc_mode; 
	sf::Vector2f acceleration_vec;
	auto rectshape = dynamic_cast<sf::RectangleShape*>(m_shape.get());

	float rotation = rectshape->getRotation();

	for (KeyboardReader::Command& dir : given_directions)
	{
		switch (dir)
		{
		case KeyboardReader::Command::Right:
			rectshape->rotate(TURN_SPEED * factor);
			break;
		case KeyboardReader::Command::Left:
			rectshape->rotate(-TURN_SPEED * factor);
			break;

		case KeyboardReader::Command::Up:
		case KeyboardReader::Command::Down:
		{
			sf::Vector2f vec = PlayerDirection();
			double f = ACCELERATION*factor;
			// double f = pow(ACCELERATION, factor);
			
			vec = ((dir == KeyboardReader::Command::Up) ? vec : -vec);
			vec = sf::Vector2f(f * vec.x, f * vec.y);
			auto add = m_moveSpeed + vec;
			m_moveSpeed = add;
			break;
		}

		case KeyboardReader::Command::Shoot:
			if (m_weapon)
			{
				sf::Vector2f dir = PlayerDirection();
				auto proj = m_weapon->produceProjectile(getCenter(), dir, game(), this);
				if (proj)
					game()->addProjectile(proj);
			}
			break;
		}
	}
}

void Player::moveByDirections(std::vector<KeyboardReader::Command> given_directions, float factor)
{
	m_moveSpeed *= (1 - FRICTION * factor);
	if (!given_directions.empty())
	{
		handleInputs(given_directions, factor);
	}	
	moveShape(m_moveSpeed*factor);
}

void Player::move(float factor)
{
	//std::vector<KeyboardReader::Direction> directions = getDirectionRemoveDuplicates(pressed_keys);
	std::vector<KeyboardReader::Command> directions = KeyboardReader::getDirections();
	moveByDirections(directions, factor);
}

