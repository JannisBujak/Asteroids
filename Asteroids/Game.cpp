#include "Game.h"

#include <qfuture.h>
#include <QtConcurrent>

Game::Game()
{
}

Game::Game(sf::Vector2f window_size)
	: sysclock(sf::Clock())
{
	init_window(window_size);
	init_variables();
}

void Game::init_window(sf::Vector2f window_size)
{
	video_mode = sf::VideoMode(window_size.x, window_size.y);
	window = std::make_shared<sf::RenderWindow>(video_mode, "Gaming", sf::Style::Close | sf::Style::Titlebar);
}

void Game::init_variables()
{
	m_player = std::make_shared<Player>(video_mode.width / 10, video_mode.height / 10, 192, this);

	m_player->setPosition(sf::Vector2f(0, 0));
	m_player->setFillColor(sf::Color::Green);
}

float Game::DeltaTime()
{
	return sysclock.restart().asSeconds();
}

const std::shared_ptr<Player> Game::getPlayer(size_t index) const
{
	return m_player;
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
	std::vector<QFuture<void>> futures;

	for (std::shared_ptr<Moveable> p : m_moveables)
	{
		futures.push_back(QtConcurrent::run([&]()
			{
				if (p.get() == nullptr)
				{
					qDebug() << "Huh";
				}else
					p->move(dt);
			}));
	}
	for (auto f : futures)
		f.waitForFinished();

	m_player->move(dt);
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

	window->draw(*m_player);
	for (std::shared_ptr<Moveable> moveable : m_moveables)
	{
		window->draw(*moveable);
	}

	window->display();
}

void Game::addIndependentMovable(std::shared_ptr<Moveable> a_moveable)
{
	m_moveables.push_back(a_moveable);
}

Game::operator bool()
{
	return (window->isOpen());
}
