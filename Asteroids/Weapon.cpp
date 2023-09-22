#include "Weapon.h"
#include "Game.h"
#include "Projectile.h"

#include <QDateTime>

std::shared_ptr<Projectile> Gun1::produceProjectile(sf::Vector2f a_pos, sf::Vector2f a_dir, Game* game, Moveable* m_shooter)
{
	int64_t now_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (now_ms - last_shot_ms > COOLDOWN_MS)
	{		
		last_shot_ms = now_ms;
		float radius = 10;
		sf::Vector2f tl_pos(a_pos.x - radius, a_pos.y - radius);

		float dir_len = sqrt(a_dir.x * a_dir.x + a_dir.y * a_dir.y);
		sf::Vector2f proj_movement(a_dir.x * BULLET_MOVEMENT_SPEED / dir_len, a_dir.y * BULLET_MOVEMENT_SPEED / dir_len);

		return std::make_shared<Projectile>(tl_pos, radius, proj_movement, game, m_shooter);
	}
	return std::shared_ptr<Projectile>();
}
