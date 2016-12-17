#pragma once

#include "texture_holder.h"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:

    void processEvents();
    void update(sf::Time);
    void draw();

    void handlePlayerInput(sf::Keyboard::Key code, bool pressed);
    void updateFpsMessage(sf::Time elapsed);

    sf::RenderWindow _window;
    TextureHolder textures{};
    sf::Sprite _playerSprite{};
    sf::Vector2f _playerMoveDirection{};
    sf::Font _messageFont{};
    sf::Text _fpsMessage{};
    sf::Time _statisticsUpdateTime{};
    std::size_t _statisticsNumberOfFrames{};
};
