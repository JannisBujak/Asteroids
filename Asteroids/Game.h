#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Moveable.h"

#include "KeyboardReader.h"

#include <QList>
#include <QMutex>

class Game
{
private:
	sf::Clock sysclock;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event ev;
	sf::VideoMode video_mode;

	std::shared_ptr<Player> m_player;

	class ProjectilesProtected
	{
	private:
		std::vector<std::shared_ptr<Moveable>> m_list;
		QMutex mutex;

	public:
		ProjectilesProtected() = default;
		ProjectilesProtected(std::vector<std::shared_ptr<Moveable>> a_list)
			: m_list(a_list)
		{}

		void addProjectile(std::shared_ptr<Moveable> a_moveable)
		{
			QMutexLocker l(&mutex);
			m_list.push_back(a_moveable);
		}

		void removeProjectile(Moveable* a_moveable)
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

	} m_projectiles;

public:
	Game();
	Game(sf::Vector2f window_size);
	
private:
	void init_window(sf::Vector2f window_size);
	void init_variables();
	

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

