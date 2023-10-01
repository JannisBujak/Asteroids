#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Moveable.h"

#include "KeyboardReader.h"

#include <QFile>

float PointDistance(sf::Vector2f a, sf::Vector2f b);
sf::Vector2f NormalizeVector(sf::Vector2f v);
uint64_t Millis();

class Game
{
private:
	sf::Clock sysclock;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event ev;
	sf::VideoMode video_mode;

	std::shared_ptr<Player> m_player;


	class MoveableMutexList : public std::vector<std::shared_ptr<Moveable>>	
	{
	public:
		bool removeObj(Moveable* a_mov)
		{
			for (auto it = begin(); it != end(); ++it)
			{
				if (it->get() == a_mov)
				{
					erase(it);
					return true;
				}
			}
			return false;
		}
	};

	MoveableMutexList m_moveables;

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

public:
	// JSON 
	static QPair<QString, QString> getPathBaename(QString a_filename);
	static bool openFileCreateDirIfNotEx(QString a_filename, QFile& a_file, QIODeviceBase::OpenMode a_openmode = QIODeviceBase::OpenModeFlag::ReadOnly);
	void saveAsJson() const;

	void poll();
	void clear_sight();
	void render();

	void addMoveable(std::shared_ptr<Moveable> a_moveable);
	void removeMoveable(Moveable* a_moveable);

	sf::FloatRect getRect() const;

	size_t num_elements() const;

public:
	operator bool();
};

