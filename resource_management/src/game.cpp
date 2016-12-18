#include "game.h"
#include <string>

namespace {

const auto kAppName = "Resource Management";
const auto kWindowWidth = 1280;
const auto kWindowHeight = 770;
const auto kPlayerSpeed = 200;
const auto kTimePerFrame = sf::seconds(1.0f / 60.0f);
// https://openclipart.org/detail/220295/airplane-pictogram-fixed
const auto kPlayerAirplaneTexturePath = "../images/airplane.png";
// https://pixabay.com/en/slovenia-mountains-sky-clouds-fog-1901151/
const auto kLandscapeTexturePath = "../images/landscape.png";
const auto kInconsolataFontPath = "Inconsolata.ttf";
const auto kLiberationFontPath = "LiberationSans-Regular.ttf";

} // namespace

Game::Game()
    : _window{sf::VideoMode(kWindowWidth, kWindowHeight), kAppName}
{
    using namespace std::string_literals;

    textures.load(Textures::Airplane, kPlayerAirplaneTexturePath);
    textures.load(Textures::Landscape, kLandscapeTexturePath);

    fonts.load(Fonts::Inconsolata, kInconsolataFontPath);
    fonts.load(Fonts::LiberationSans, kLiberationFontPath);

    _window.setVerticalSyncEnabled(true);
    _playerSprite.setTexture(textures.get(Textures::Airplane));
    _playerSprite.setPosition(kWindowWidth / 2, kWindowHeight / 2);

    _fpsMessage.setFont(fonts.get(Fonts::Inconsolata));
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

    auto landscape = sf::Sprite{};
    landscape.setTexture(textures.get(Textures::Landscape));

    _window.draw(landscape);
    _window.draw(_playerSprite);
    _window.display();
}
