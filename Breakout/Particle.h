#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>

#include <iostream>
using namespace std;

class Particle
{
public:
    Particle(float x, float y, float minRadius);
    ~Particle();
    void render(sf::RenderWindow& window);
    void Update(float dt);
    bool GetIsActive() { return isActive; }
    void Explode(sf::Vector2f pos);
private:
    sf::CircleShape shape;
    bool isActive = false;
    float x = 0, y = 0;
    float directionX = 0, directionY = 0;

    float stepCooldown = 0.015f;
    float currentTimer = 0.2f;
    int steps = 0;
    sf::Vector2f randomDirection;

    float deathTimer = 0; //just in case
};

