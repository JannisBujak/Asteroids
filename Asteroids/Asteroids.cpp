// Asteroids.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Game.h"
#include <filesystem>
#include <cstdio>
#include <thread>

#include <QString>
#include <QDateTime>

const float OrientedWidth = 1920, OrientedHeight = 1080;

int main(int argc, char** argv)
{
    Game game(sf::Vector2f(1920, 1080));
    sf::Text time_gone_text;

    // Declare a new font
    sf::Font font;
    
    // Beispielcode zum Laden aus JSON, 
    // TODO: In Game::Init verwenden
#if 0     
    // Load it from a file
    QFile json;
    bool succ = openFileCreateDirIfNotEx(QString("%1/temp/Asteroids/Levels.json").arg(QDir::homePath()), json, QIODeviceBase::Truncate | QIODeviceBase::ReadWrite);

    QJsonObject obj(
        { 
            {"Name", "grag"}, 
            {"a", 5},
            {"b", 6}
        });
    QJsonObject obj2;
    QJsonArray arr;
    if(!obj.empty())
        arr.push_back(obj);

    if(!obj2.empty())
        arr.push_back(obj2);
    
    int w1 = json.write(QJsonDocument(arr).toJson(QJsonDocument::Compact));    
#endif

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
    
    bool limitFPS = false;
    uint64_t listFPSToggleTS = 0;
    uint64_t now_ms;

    while ((bool)game)
    {
        game.poll();
        
        std::vector<KeyboardReader::Command> commands = KeyboardReader::getDirections();
        for (KeyboardReader::Command& dir : commands)
        {
            switch (dir)
            {
            case KeyboardReader::Command::SwitchLimitFPS:
                now_ms = Millis();
                if (now_ms - listFPSToggleTS > 1000)
                {
                    limitFPS = !limitFPS;
                    std::cout << "Limit fps set to " << limitFPS << std::endl;
                    listFPSToggleTS = now_ms;
                }
                    break;
                case KeyboardReader::Command::Reset:
                    game.ReinitMoveables();             
                    
                    break;
            }
        }

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
                
                std::string message = QString().asprintf("%.0f fps, %u obj", fps, game.num_elements()).toStdString();
                time_gone_text.setString(message.c_str());

                time_gone_text.setPosition(sf::Vector2f((OrientedWidth - 2 * time_gone_text.getLocalBounds().width), (OrientedHeight - 2 * time_gone_text.getLocalBounds().height)));
            }
        }
        else millis_gone = 0;
        
        game.clear_sight();
        game.draw(time_gone_text);
        game.render();
        if (limitFPS)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }

    }
    
    // Clears contents
    QFile json;
    json.resize(0);
    
    // save state of the level     
    game.saveAsJson();

    
    return 0;
}

