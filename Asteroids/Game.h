#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Moveable.h"

#include "KeyboardReader.h"

#include <QList>

class Game
{
private:
	sf::Clock sysclock;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event ev;
	sf::VideoMode video_mode;

	std::shared_ptr<Player> m_player;
	QList<std::shared_ptr<Moveable>> m_moveables;

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

	void addIndependentMovable(std::shared_ptr<Moveable> a_moveable);

public:
	operator bool();
};

