#include "Particle.h"

Particle::Particle(float x, float y, float radius)
{
    shape.setPosition(x, y);
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Magenta);
}

Particle::~Particle() {

}

void Particle::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(shape);
    }
}