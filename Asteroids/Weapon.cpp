#include "Weapon.h"
#include "Game.h"
#include "Projectile.h"

#include <QDateTime>

std::shared_ptr<Projectile> Gun1::produceProjectile(sf::Vector2f pos, Game* game)
{
	int64_t now_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if (now_ms - last_shot_ms > cooldown_ms)
	{		
		last_shot_ms = now_ms;
		return std::make_shared<Projectile>(pos, sf::Vector2f(10, 10), sf::Vector2f(100, 0), game);
	}
	return std::shared_ptr<Projectile>();
}
