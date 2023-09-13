#include "Game.h"

Game::Game()
{
}

Game::Game(sf::Vector2f window_size)
	: sysclock(sf::Clock())
{
	init_window(window_size);
	init_variables();
}

Game::~Game()
{
	delete window;
	
	for (Moveable* moveable : players)
	{
		delete moveable;
	}
}

void Game::init_window(sf::Vector2f window_size)
{
	video_mode = sf::VideoMode(window_size.x, window_size.y);
	window = new sf::RenderWindow(video_mode, "Gaming", sf::Style::Close | sf::Style::Titlebar);
}

void Game::init_variables()
{
	Player* player = new Player(video_mode.width / 10, video_mode.height / 10, 192);

	player->setPosition(sf::Vector2f(0, 0));
	player->setFillColor(sf::Color::Green);
	players.push_back(player);
}

float Game::DeltaTime()
{
	return sysclock.restart().asSeconds();
}

const Player* Game::getPlayer(size_t index) const
{
	if (index >= players.size())
		return nullptr;
	return (Player*)(players.at(index));
}

void Game::draw(sf::Drawable& drawable)
{
	if (window)
		window->draw(drawable);
}

float Game::update(int& keyTime)
{
	if (keyTime++ < KeyboardReader::KeyTargetTime - 1) {
		return 0;
	}

	float dt = DeltaTime();

	for(Moveable* p : players)
		p->move(dt);

	keyTime = 0;

	return dt;
}

void Game::poll()
{
	if (!window)
		return;
	
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close(); break;
		case sf::Event::Resized:
			break;
		}
	}
}

void Game::clear_sight()
{
	if (!window)
		return;

	window->clear();
}

void Game::render()
{
	if (!window)
		return;

	for (Moveable* moveable : players)
	{
		window->draw(*moveable);
	}

	window->display();
}

Game::operator bool()
{
	return (window->isOpen());
}
