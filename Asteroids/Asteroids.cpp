// Asteroids.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Game.h"
#include <filesystem>
#include <QString>

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

    double millis_gone = 0, cycle_time, fps;
    int keyTime = 0;

    while ((bool)game)
    {
        game.poll();
                
        cycle_time = game.update(keyTime);
        millis_gone += cycle_time;
        
        const std::shared_ptr<Player> p = game.getPlayer();
        if (p->getPosition().x < 0)
        {
            millis_gone = 0;
        }
        else if (p->getPosition().x + p->getSize().x < OrientedWidth) {
            if (cycle_time)
            {
                fps = (cycle_time != 0) ? (1 / cycle_time) : 0;
                time_gone_text.setString(QString().asprintf("%.0f fps, %d obj", fps, game.num_elements()).toStdString());
                // std::cout << ((std::string)time_gone_text.getString()) << std::endl;
                time_gone_text.setPosition(sf::Vector2f((OrientedWidth - 2 * time_gone_text.getLocalBounds().width), (OrientedHeight - 2 * time_gone_text.getLocalBounds().height)));
            }
        }
        else millis_gone = 0;
        
        game.clear_sight();
        game.draw(time_gone_text);
        game.render();
    }
    return 0;
}

