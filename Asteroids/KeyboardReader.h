#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>

class KeyboardReader
{
public:
	enum class Command {
		Up,
		Right,
		Down,
		Left,
		Shoot,
		None
	};

private:
	// member variable(s)
	using KeyMapping = std::map<sf::Keyboard::Key, KeyboardReader::Command>;
	KeyMapping key_map;


public:
	// static variable(s)
	const static char KeyTargetTime = 8;

	static KeyboardReader::Command getOpposite(KeyboardReader::Command direction);

	void initializeKeyMap();

	KeyboardReader() 
	{
		initializeKeyMap();
	}

public:
	static void RemoveFoundViaFunction(std::vector<KeyboardReader::Command>& directions, KeyboardReader::Command(*fun)(KeyboardReader::Command), bool remove_first_of_kind);

	// converts the given Keys to Directions via the mapping
	std::vector<KeyboardReader::Command> convertKeysToDirections(const std::vector<sf::Keyboard::Key>& pressed_keys);

	// uses convertKeysToDirections() to remove duplicate and opposite directions 
	std::vector<Command> convertToDirectionsRemoveUnnecessary(std::vector<sf::Keyboard::Key>& pressed_keys);

public:
	/*
	* Functions accessing the Singleton
	*/

	static KeyboardReader& getSingleton() 
	{
		static KeyboardReader kbReader;
		return kbReader;
	}

	// receive all currently pressed keys
	static std::vector <sf::Keyboard::Key> getPressedKeys();


	// uses remaining Functions to return only Directions
	static std::vector<KeyboardReader::Command> getDirections();

	// Testing
	void TestDirectionFilder();

};

