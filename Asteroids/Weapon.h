#pragma once


// #include "Projectile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <QString>

class Game;
class Moveable;

class Weapon
{
protected:
	int64_t last_shot_ms;
public:
	virtual int64_t getCooldown() const = 0;
	virtual int64_t getBulletMovementSpeed() const = 0;
	virtual int64_t getTimeOfExistence() const = 0;

	virtual std::shared_ptr<Moveable> produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game, Moveable* m_shooter);
	
	virtual QString getWeaponName() const = 0;
};

class Gun1 : public Weapon
{
	const static int64_t COOLDOWN_MS = 300;
	inline const static int64_t BULLET_MOVEMENT_SPEED = 1000;
public:
	Gun1() = default;

	virtual int64_t getCooldown() const override;
	virtual int64_t getBulletMovementSpeed() const override;
	virtual int64_t getTimeOfExistence() const override;

	virtual QString getWeaponName() const override;
};


class TurretGun1 : public Weapon
{
	const static int64_t COOLDOWN_MS = 1000;
	inline const static int64_t BULLET_MOVEMENT_SPEED = 100;
public:
	TurretGun1() = default;

	virtual int64_t getCooldown() const override;
	virtual int64_t getBulletMovementSpeed() const override;
	virtual int64_t getTimeOfExistence() const override;
	
	virtual QString getWeaponName() const override;
};
