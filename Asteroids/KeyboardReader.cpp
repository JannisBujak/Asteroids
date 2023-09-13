#include "KeyboardReader.h"


KeyboardReader::Direction KeyboardReader::getOpposite(KeyboardReader::Direction direction)
{
	switch (direction) {
	case KeyboardReader::Direction::Up:
		return KeyboardReader::Direction::Down;
	case KeyboardReader::Direction::Right:
		return KeyboardReader::Direction::Left;
	case KeyboardReader::Direction::Down:
		return KeyboardReader::Direction::Up;
	case KeyboardReader::Direction::Left:
		return KeyboardReader::Direction::Right;
	default:
		return KeyboardReader::Direction::None;
	}
}

void KeyboardReader::initializeKeyMap()
{
	using KeyMapping = std::pair<sf::Keyboard::Key, KeyboardReader::Direction>;
	std::pair<sf::Keyboard::Key, KeyboardReader::Direction> mappings[] = {
		{sf::Keyboard::Up, KeyboardReader::Direction::Up},
		{sf::Keyboard::W, KeyboardReader::Direction::Up},
		{sf::Keyboard::Right, KeyboardReader::Direction::Right},
		{sf::Keyboard::D, KeyboardReader::Direction::Right},
		{sf::Keyboard::Down, KeyboardReader::Direction::Down},
		{sf::Keyboard::S, KeyboardReader::Direction::Down},
		{sf::Keyboard::Left, KeyboardReader::Direction::Left},
		{sf::Keyboard::A, KeyboardReader::Direction::Left}
	};
	for (KeyMapping& mapping : mappings)
	{
		key_map.insert(mapping);
	}
}

void KeyboardReader::RemoveFoundViaFunction(std::vector<Direction>& directions, Direction(*fun)(Direction), bool remove_first_of_kind)
{
	using DirectionVec = std::vector<KeyboardReader::Direction>;
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

std::vector<KeyboardReader::Direction> KeyboardReader::convertKeysToDirections(const std::vector<sf::Keyboard::Key>& pressed_keys)
{
	std::vector<KeyboardReader::Direction> directions;
	for (const sf::Keyboard::Key& key : pressed_keys)
	{
		KeyMapping::iterator it = key_map.find(key);
		if(it != key_map.end())
			directions.push_back(it->second);
	}
	return directions;
}

std::vector<KeyboardReader::Direction> KeyboardReader::convertToDirectionsRemoveUnnecessary(std::vector<sf::Keyboard::Key>& pressed_keys)
{
	std::vector<Direction> directions = convertKeysToDirections(pressed_keys);
	RemoveFoundViaFunction(directions, [](Direction dir) { return dir; 	}, false);
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

std::vector<KeyboardReader::Direction> KeyboardReader::getDirections()
{
	std::vector<sf::Keyboard::Key> pressed_keys = getPressedKeys();
	if (pressed_keys.empty())
		return std::vector<KeyboardReader::Direction>();
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
	std::vector<KeyboardReader::Direction> vectors[sizeof(tests) / sizeof(tests[0])];
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		vectors[i] = convertToDirectionsRemoveUnnecessary(tests[i]);
	}

}
