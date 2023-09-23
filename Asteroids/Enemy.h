#pragma once

#include "Moveable.h"
#include "Weapon.h"

class ShootingEnemy : public Moveable
{
private:

protected:
	std::shared_ptr<Weapon> m_weapon;
	
public:
	ShootingEnemy(Game* a_game);

	virtual std::shared_ptr<Weapon> getWeapon() const = 0;
	virtual float getRange() const = 0;

	virtual const sf::Vector2f& getSize() const override;	
};

class Turret1 : public ShootingEnemy
{
private:
	inline const static int TURRET_RADIUS = 50;
	inline const static int TURRET_RANGE = 500;

public:
	Turret1(sf::Vector2f a_pos, Game* a_game);
	virtual std::shared_ptr<Weapon> getWeapon() const override;
	virtual float getRange() const override;
	virtual void move(float factor) override;
};
