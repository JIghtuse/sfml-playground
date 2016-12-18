#pragma once

#include "fonts.h"
#include "textures.h"
#include "resource_holder.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    using TextureHolder = ResourceHolder<sf::Texture, Textures>;
    using FontHolder = ResourceHolder<sf::Font, Fonts>;

    void processEvents();
    void update(sf::Time);
    void draw();

    void handlePlayerInput(sf::Keyboard::Key code, bool pressed);
    void updateFpsMessage(sf::Time elapsed);

    sf::RenderWindow _window;
    TextureHolder textures{};
    FontHolder fonts{};
    sf::Sprite _playerSprite{};
    sf::Vector2f _playerMoveDirection{};
    sf::Text _fpsMessage{};
    sf::Time _statisticsUpdateTime{};
    std::size_t _statisticsNumberOfFrames{};
};
