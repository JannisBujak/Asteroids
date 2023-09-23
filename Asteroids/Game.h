#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Moveable.h"

#include "KeyboardReader.h"

#include <QList>
#include <QMutex>

float PointDistance(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f NormalizeVector(sf::Vector2f v);

class Game
{
private:
	sf::Clock sysclock;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event ev;
	sf::VideoMode video_mode;

	std::shared_ptr<Player> m_player;

	class MoveableMutexList
	{
	private:
		std::vector<std::shared_ptr<Moveable>> m_list;
		QMutex mutex;

	public:
		MoveableMutexList() = default;

		MoveableMutexList(std::vector<std::shared_ptr<Moveable>> a_list)
			: m_list(a_list)
		{

		}

		void addObj(std::shared_ptr<Moveable> a_projectile)
		{
			QMutexLocker l(&mutex);
			m_list.push_back(a_projectile);
		}

		void removeObj(Moveable* a_moveable)
		{
			QMutexLocker l(&mutex);
			for (auto it = m_list.begin(); it != m_list.end(); ++it)
			{
				if (it->get() == a_moveable)
				{
					m_list.erase(it);
					break;
				}
			}
		}

		void clearList()
		{
			QMutexLocker l(&mutex);
			m_list.clear();
		}

		const std::vector<std::shared_ptr<Moveable>> getList() const
		{
			return m_list;
		}

		void setList(std::vector<std::shared_ptr<Moveable>> a_list)
		{
			m_list = a_list;
		}

		size_t num_elements() const
		{
			return m_list.size();
		}

	};
	MoveableMutexList m_projectiles;
	MoveableMutexList m_enemies;

public:
	Game();
	Game(sf::Vector2f window_size);

private:
	void init_window(sf::Vector2f window_size);
	
public:
	void ReinitMoveables();

public:
	float DeltaTime();

	const std::shared_ptr<Player> getPlayer(size_t index = 0) const;
	
public:
	void draw(sf::Drawable& drawable);

	float update(int& keyTime);

	void poll();
	void clear_sight();
	void render();

	void addProjectile(std::shared_ptr<Moveable> a_moveable);
	void removeProjectile(Moveable* a_moveable);

	sf::FloatRect getRect() const;

	size_t num_elements() const;

public:
	operator bool();
};

