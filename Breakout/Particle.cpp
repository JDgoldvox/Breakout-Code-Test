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
    if (isActive) {
        window.draw(shape);
    }
}

void Particle::Update(float dt) {
    if (currentTimer > 0) {
        currentTimer -= dt;
        return;
    }
    else {
        currentTimer = stepCooldown;
        steps++;
    }

    if (steps == 10) {
        isActive = false;
    }

}

void Particle::Explode(sf::Vector2f pos) {
    //set initial position
    isActive = true;
    shape.setPosition(pos);
    cout << pos.x << ' ' << pos.y << '\n';
}