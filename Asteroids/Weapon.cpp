#include "Weapon.h"
#include "Game.h"
#include "Projectile.h"

#include <QDateTime>

std::shared_ptr<Projectile> Gun1::produceProjectile(sf::Vector2f a_pos, Game* game)
{
	int64_t now_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (now_ms - last_shot_ms > cooldown_ms)
	{		
		last_shot_ms = now_ms;
		float radius = 10;
		sf::Vector2f tl_pos(a_pos.x - radius, a_pos.y - radius);
		return std::make_shared<Projectile>(tl_pos, radius, sf::Vector2f(100, 0), game);
	}
	return std::shared_ptr<Projectile>();
}
