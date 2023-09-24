#include "Game.h"

#include "Weapon.h"
#include "Enemy.h"
#include <chrono>

/*
#include <qfuture.h>
#include <QtConcurrent>
*/

float PointDistance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y-a.y, 2));
}

sf::Vector2f NormalizeVector(sf::Vector2f v)
{
	float len = 1 / sqrt(v.x * v.x + v.y * v.y);
	return sf::Vector2f(v.x * len, v.y * len);
}

uint64_t Millis()
{
	uint64_t millis;
	using namespace std::chrono;
	time_point<system_clock> now =
		system_clock::now();
	auto duration = now.time_since_epoch();
	millis = duration_cast<milliseconds>(duration).count();
	return millis;
}

Game::Game()
{
}

Game::Game(sf::Vector2f window_size)
	: sysclock(sf::Clock())
{
	init_window(window_size);
	ReinitMoveables();
}

void Game::init_window(sf::Vector2f window_size)
{
	video_mode = sf::VideoMode(window_size.x, window_size.y);
	window = std::make_shared<sf::RenderWindow>(video_mode, "Gaming", sf::Style::Close | sf::Style::Titlebar);
}

void Game::ReinitMoveables()
{
	// Player 
	m_player = std::make_shared<Player>(video_mode.width / 10, video_mode.height / 10, 192, std::make_shared<Gun1>(), this);

	m_player->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	m_player->setFillColor(sf::Color::Green);
	
	// Projectiles
	m_projectiles.clearList();

	// Enemies
	m_enemies.clearList();
	std::shared_ptr<ShootingEnemy> e = std::make_shared<Turret1>(sf::Vector2f(video_mode.width * 0.9, video_mode.height * 0.9), this);
	m_enemies.addObj(e);
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

void callMove(std::shared_ptr<Moveable> mov, float dt)
{
	mov->move(dt);
}

float Game::update(int& keyTime)
{
	if (keyTime++ < KeyboardReader::KeyTargetTime - 1) {
		return 0;
	}

	float dt = DeltaTime();
	if (dt == 0)
		return 0;

	MoveableMutexList projectiles_copy(m_projectiles.getList());

	for (std::shared_ptr<Moveable> p : projectiles_copy.getList())
	{
		p->move(dt);
	}

	for (std::shared_ptr<Moveable> enemy : m_enemies.getList())
	{
		enemy->move(dt);
	}
	
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

	window->draw(*m_player->shape());
	for (std::shared_ptr<Moveable> moveable : m_projectiles.getList())
	{
		window->draw(*moveable->shape());
	}
	for (std::shared_ptr<Moveable> enemy : m_enemies.getList())
	{
		window->draw(*enemy->shape());
	}

	window->display();
}

void Game::addProjectile(std::shared_ptr<Moveable> a_moveable)
{
	m_projectiles.addObj(a_moveable);
}

void Game::removeProjectile(Moveable* a_moveable)
{
	m_projectiles.removeObj(a_moveable);
}

sf::FloatRect Game::getRect() const
{
	return sf::FloatRect(0, 0, video_mode.width, video_mode.height);
}

size_t Game::num_elements() const
{
	return 1 + m_projectiles.num_elements();
}

Game::operator bool()
{
	return (window->isOpen());
}

