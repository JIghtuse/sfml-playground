#include <SFML/Graphics.hpp>

namespace {

const auto kAppName = "SFML Application";
const auto kWindowWidth = 640;
const auto kWindowHeight = 480;

} // namespace

int main()
{
    auto &&window = sf::RenderWindow(sf::VideoMode(kWindowWidth, kWindowHeight), kAppName);

    const auto circleRadius = 80;
    auto shape = sf::CircleShape{circleRadius};
    shape.setPosition(kWindowWidth / 2 - circleRadius, kWindowHeight / 2 - circleRadius);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
}
