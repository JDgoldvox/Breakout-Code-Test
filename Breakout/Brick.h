#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    float xPos = 0, yPos = 0;
private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};