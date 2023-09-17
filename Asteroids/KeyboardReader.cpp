#include "KeyboardReader.h"


KeyboardReader::Command KeyboardReader::getOpposite(KeyboardReader::Command direction)
{
	switch (direction) {
	case KeyboardReader::Command::Up:
		return KeyboardReader::Command::Down;
	case KeyboardReader::Command::Right:
		return KeyboardReader::Command::Left;
	case KeyboardReader::Command::Down:
		return KeyboardReader::Command::Up;
	case KeyboardReader::Command::Left:
		return KeyboardReader::Command::Right;
	default:
		return KeyboardReader::Command::None;
	}
}

void KeyboardReader::initializeKeyMap()
{
	using KeyMapping = std::pair<sf::Keyboard::Key, KeyboardReader::Command>;
	std::pair<sf::Keyboard::Key, KeyboardReader::Command> mappings[] = {
		{sf::Keyboard::Up, KeyboardReader::Command::Up},
		{sf::Keyboard::W, KeyboardReader::Command::Up},
		{sf::Keyboard::Right, KeyboardReader::Command::Right},
		{sf::Keyboard::D, KeyboardReader::Command::Right},
		{sf::Keyboard::Down, KeyboardReader::Command::Down},
		{sf::Keyboard::S, KeyboardReader::Command::Down},
		{sf::Keyboard::Left, KeyboardReader::Command::Left},
		{sf::Keyboard::A, KeyboardReader::Command::Left},
		{sf::Keyboard::Space, KeyboardReader::Command::Shoot},

	};
	for (KeyMapping& mapping : mappings)
	{
		key_map.insert(mapping);
	}
}

void KeyboardReader::RemoveFoundViaFunction(std::vector<Command>& directions, Command(*fun)(Command), bool remove_first_of_kind)
{
	using DirectionVec = std::vector<KeyboardReader::Command>;
	std::vector<DirectionVec::iterator> toDelete;
	for (DirectionVec::iterator it = directions.begin(); it < directions.end(); it++)
	{
		DirectionVec::iterator equal_result;
		bool nextIsFirst = true;
		while ((equal_result = std::find(it + 1, directions.end(), fun(*it))) < directions.end())
		{
			directions.erase(equal_result);
			if (remove_first_of_kind && nextIsFirst)
				toDelete.push_back(it);

			nextIsFirst = false;
		}
	}

	for (int i = toDelete.size() - 1; i >= 0; i--)
		directions.erase(directions.begin() + i);
}

std::vector<KeyboardReader::Command> KeyboardReader::convertKeysToDirections(const std::vector<sf::Keyboard::Key>& pressed_keys)
{
	std::vector<KeyboardReader::Command> directions;
	for (const sf::Keyboard::Key& key : pressed_keys)
	{
		KeyMapping::iterator it = key_map.find(key);
		if(it != key_map.end())
			directions.push_back(it->second);
	}
	return directions;
}

std::vector<KeyboardReader::Command> KeyboardReader::convertToDirectionsRemoveUnnecessary(std::vector<sf::Keyboard::Key>& pressed_keys)
{
	std::vector<Command> directions = convertKeysToDirections(pressed_keys);
	RemoveFoundViaFunction(directions, [](Command dir) { return dir; 	}, false);
	RemoveFoundViaFunction(directions, getOpposite, true);
	return directions;
}

std::vector<sf::Keyboard::Key> KeyboardReader::getPressedKeys()
{
	std::vector <sf::Keyboard::Key> pressed_keys;
	KeyMapping& mapping = getSingleton().key_map;
	for (KeyMapping::iterator it = mapping.begin(); it != mapping.end(); it++)
	{
		if (sf::Keyboard::isKeyPressed(it->first))
			pressed_keys.push_back(it->first);
	}
	return pressed_keys;
}

std::vector<KeyboardReader::Command> KeyboardReader::getDirections()
{
	std::vector<sf::Keyboard::Key> pressed_keys = getPressedKeys();
	if (pressed_keys.empty())
		return std::vector<KeyboardReader::Command>();
	return getSingleton().convertToDirectionsRemoveUnnecessary(pressed_keys);
}

void KeyboardReader::TestDirectionFilder()
{
	std::vector<sf::Keyboard::Key> tests[] = {
		std::vector<sf::Keyboard::Key>({
			sf::Keyboard::W,
			sf::Keyboard::Up,
			sf::Keyboard::W
		}),
		std::vector<sf::Keyboard::Key>({
			sf::Keyboard::W,
			sf::Keyboard::Left,
			sf::Keyboard::Up,
			sf::Keyboard::W,
			sf::Keyboard::D,
			sf::Keyboard::Down
		})
	};
	std::vector<KeyboardReader::Command> vectors[sizeof(tests) / sizeof(tests[0])];
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		vectors[i] = convertToDirectionsRemoveUnnecessary(tests[i]);
	}

}
