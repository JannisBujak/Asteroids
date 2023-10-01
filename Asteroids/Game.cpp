#include "Game.h"

#include "Weapon.h"
#include "Enemy.h"
#include <chrono>

#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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
	
	// Projectiles & Enemies
	m_moveables.clear();
	m_moveables.push_back(m_player);
	
	std::shared_ptr<ShootingEnemy> e = std::make_shared<Turret1>(sf::Vector2f(video_mode.width * 0.9, video_mode.height * 0.9), this);
	m_moveables.push_back(e);
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
	
	MoveableMutexList moveables_copy(m_moveables);
	for (std::shared_ptr<Moveable> m : moveables_copy)
	{
		m->move(dt);
	}
	
	keyTime = 0;

	return dt;
}

QPair<QString, QString> Game::getPathBaename(QString a_filename)
{
	QFileInfo info(a_filename);
	QString basename = info.fileName();
	return QPair<QString, QString>(a_filename.remove(basename), basename);
}

bool Game::openFileCreateDirIfNotEx(QString a_filename, QFile& a_file, QIODeviceBase::OpenMode a_openmode)
{
	auto [path, filename] = getPathBaename(a_filename);
	QDir dir(path);

	if (!dir.exists())
	{
		if (!dir.mkpath("."))
			return false;
	}
	a_file.setFileName(a_filename);
	return a_file.open(a_openmode);
}

void Game::saveAsJson() const
{
	QFile jsonfile;
	bool succ = openFileCreateDirIfNotEx(QString("%1/temp/Asteroids/Levels.json").arg(QDir::homePath()), jsonfile, QIODeviceBase::Truncate | QIODeviceBase::ReadWrite);

	QJsonArray array;
	for (auto& m : m_moveables)
	{
		auto json_obj = m->toJson();
		if (!json_obj.empty())
		{
			array.push_back(json_obj);
		}
	}
	int written = jsonfile.write(QJsonDocument(array).toJson(QJsonDocument::Compact));
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

	for (std::shared_ptr<Moveable> moveable : m_moveables)
	{
		window->draw(*moveable->shape());
	}
	
	window->display();
}

void Game::addMoveable(std::shared_ptr<Moveable> a_moveable)
{
	m_moveables.push_back(a_moveable);
}

void Game::removeMoveable(Moveable* a_moveable)
{	
	m_moveables.removeObj(a_moveable);	
}

sf::FloatRect Game::getRect() const
{
	return sf::FloatRect(0, 0, video_mode.width, video_mode.height);
}

size_t Game::num_elements() const
{
	return 1 + m_moveables.size();
}

Game::operator bool()
{
	return (window->isOpen());
}

