#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Moveable.h"

#include "KeyboardReader.h"


class Game
{
private:
	sf::Clock sysclock;
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode video_mode;

	Player* m_player;
	std::vector<Moveable*> m_moveables;

public:
	Game();
	Game(sf::Vector2f window_size);
	~Game();

private:
	void init_window(sf::Vector2f window_size);
	void init_variables();
	

public:
	float DeltaTime();

	const Player* getPlayer(size_t index = 0) const;
	
public:
	void draw(sf::Drawable& drawable);

	float update(int& keyTime);

	void poll();
	void clear_sight();
	void render();


public:
	operator bool();
};

