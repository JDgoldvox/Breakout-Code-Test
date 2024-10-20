#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(float x, float y, float radius);
    ~Particle();
    void render(sf::RenderWindow& window);

private:
    sf::CircleShape shape;
    bool _isDestroyed = false;
    float x = 0, y = 0;
    float directionX = 0, directionY = 0;
};

