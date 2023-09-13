// Asteroids.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Game.h"
#include <filesystem>

const float OrientedWidth = 1920, OrientedHeight = 1080;

int main(int argc, char** argv)
{
    Game game(sf::Vector2f(1920, 1080));
        
    sf::Text time_gone_text;

    // Declare a new font
    sf::Font font;
    // Load it from a file

    if (!font.loadFromFile("../../../../res/arial.ttf"))
    {
        // error...
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    time_gone_text.setFont(font);

    time_gone_text.setFillColor(sf::Color::White);
    time_gone_text.setCharacterSize(12);

    double millis_gone = 0;
    int keyTime = 0;

    while ((bool)game)
    {
        game.poll();
                
        millis_gone += game.update(keyTime);

        const Player* p = game.getPlayer();
        if (p->getPosition().x < 0)
        {
            millis_gone = 0;
        }
        else if (p->getPosition().x + p->getSize().x < OrientedWidth) {
            time_gone_text.setString(std::to_string(millis_gone));
            time_gone_text.setPosition(sf::Vector2f((OrientedWidth - time_gone_text.getLocalBounds().width), (OrientedHeight - 2*time_gone_text.getLocalBounds().height)));
        }
        else millis_gone = 0;
        
        game.clear_sight();
        game.draw(time_gone_text);
        game.render();
    }

    return 0;
}

