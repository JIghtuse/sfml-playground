#include "game.h"
#include <string>

namespace {

const auto kAppName = "Sprites";
const auto kWindowWidth = 1280;
const auto kWindowHeight = 960;
const auto kPlayerSpeed = 200;
const auto kTimePerFrame = sf::seconds(1.0f / 60.0f);
const auto kPlayerTexturePath = "../images/player.png";
const auto kMessageFontPath = "Inconsolata.ttf";

} // namespace

Game::Game()
    : _window{sf::VideoMode(kWindowWidth, kWindowHeight), kAppName}
    , _playerTexture{}
    , _playerSprite{}
    , _playerMoveDirection{}
    , _messageFont{}
    , _fpsMessage{}
    , _statisticsUpdateTime{}
    , _statisticsNumberOfFrames{}
{
    using namespace std::string_literals;

    if (!_playerTexture.loadFromFile(kPlayerTexturePath)) {
        throw std::runtime_error("Cannot load player texture file "s + kPlayerTexturePath);
    }
    if (!_messageFont.loadFromFile(kMessageFontPath)) {
        throw std::runtime_error("Cannot load message font file "s + kMessageFontPath);
    }

    _window.setVerticalSyncEnabled(true);
    _playerSprite.setTexture(_playerTexture);
    _playerSprite.setScale(2, 2);
    _playerSprite.setPosition(kWindowWidth / 2, kWindowHeight / 2);

    _fpsMessage.setFont(_messageFont);
    _fpsMessage.setCharacterSize(50);
    _fpsMessage.setColor(sf::Color::Black);

}

void Game::run()
{
    auto clock = sf::Clock();
    auto timeSinceLastUpdate = sf::Time::Zero;

    while (_window.isOpen())
    {
        processEvents();
        auto elapsed = clock.restart();
        timeSinceLastUpdate += elapsed;
        while (timeSinceLastUpdate > kTimePerFrame) {
            timeSinceLastUpdate -= kTimePerFrame;
            processEvents();
            update(kTimePerFrame);
        }
        updateFpsMessage(elapsed);
        draw();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key code, bool pressed)
{
    if (pressed) {
        switch (code) {
        case sf::Keyboard::W:
            _playerMoveDirection = {0.0f, -kPlayerSpeed};
            break;
        case sf::Keyboard::S:
            _playerMoveDirection = {0.0f, kPlayerSpeed};
            break;
        case sf::Keyboard::A:
            _playerMoveDirection = {-kPlayerSpeed, 0.0f};
            break;
        case sf::Keyboard::D:
            _playerMoveDirection = {kPlayerSpeed, 0.0f};
            break;
        default:
            break;
        }
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            _window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update(sf::Time delta)
{
    _playerSprite.move(_playerMoveDirection * delta.asSeconds());
}

void Game::updateFpsMessage(sf::Time elapsed)
{
    using namespace std::string_literals;

    _statisticsUpdateTime += elapsed;
    _statisticsNumberOfFrames++;

    if (_statisticsUpdateTime >= sf::seconds(1.0f)) {
        _fpsMessage.setString("FPS: "s + std::to_string(_statisticsNumberOfFrames));
        _statisticsUpdateTime -= sf::seconds(1.0f);
        _statisticsNumberOfFrames = 0;
    }
}

void Game::draw()
{
    _window.clear(sf::Color::White);
    _window.draw(_fpsMessage);
    _window.draw(_playerSprite);
    _window.display();
}
