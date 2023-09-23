#include "Weapon.h"
#include "Game.h"
#include "Projectile.h"

#include <QDateTime>


std::shared_ptr<Moveable> Weapon::produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game, Moveable* m_shooter)
{
	int64_t now_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (now_ms - last_shot_ms > getCooldown())
	{
		last_shot_ms = now_ms;
		float radius = 10;
		sf::Vector2f tl_pos(a_pos.x - radius, a_pos.y - radius);

		float dir_len = sqrt(a_dir.x * a_dir.x + a_dir.y * a_dir.y);
		sf::Vector2f proj_movement(a_dir.x * getBulletMovementSpeed() / dir_len, a_dir.y * getBulletMovementSpeed() / dir_len);

		return std::make_shared<Projectile>(tl_pos, radius, proj_movement, game, m_shooter);
	}
	return std::shared_ptr<Projectile>();
}

int64_t Gun1::getCooldown() const
{
	return COOLDOWN_MS;
}

int64_t Gun1::getBulletMovementSpeed() const
{
	return BULLET_MOVEMENT_SPEED;
}

int64_t TurretGun1::getCooldown() const
{
	return COOLDOWN_MS;
}

int64_t TurretGun1::getBulletMovementSpeed() const
{
	return BULLET_MOVEMENT_SPEED;
}
