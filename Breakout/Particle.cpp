#include "Particle.h"

Particle::Particle(float x, float y, float minRadius)
{
    shape.setPosition(x, y);
    shape.setRadius(rand() % 20 + minRadius);
    shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255 + 50));
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
    deathTimer += dt;
    if (deathTimer >= 3) {
        isActive = false;
        deathTimer = 0;
        return;
    }

    if (!isActive) {
        return;
    }

    if (currentTimer > 0) {
        currentTimer -= dt;
        return;
    }
    else {
        currentTimer = stepCooldown;
        steps++;
    }
    
    //move sprite
    shape.move({randomDirection.x * 30, randomDirection.y * 30});

    if (steps == 30) {
        isActive = false;
    }

}

void Particle::Explode(sf::Vector2f pos) {
    
    //set initial position
    isActive = true;
    shape.setPosition(pos);

    //set random direction to move
    float x = std::rand() % 10 + 1;
    float y = std::rand() % 10 + 1;

    sf::Vector2f randomPos;

    int randomNum = std::rand() % 4;
    if (randomNum == 1) {
        randomPos = { pos.x + x, pos.y + y };
    }
    else if(randomNum == 2)
    {
        randomPos = { pos.x - x, pos.y - y };
    }
    else if (randomNum == 3)
    {
        randomPos = { pos.x + x, pos.y - y };
    }
    else {
        randomPos = { pos.x - x, pos.y + y };
    }
    
    randomDirection = pos - randomPos;
    randomDirection = {1/randomDirection.x, 1/randomDirection.y };
}