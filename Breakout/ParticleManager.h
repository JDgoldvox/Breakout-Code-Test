#pragma once
#include <vector>
#include "Particle.h"
#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;

using std::vector;

class GameManager;

class ParticleManager
{
public:
    ParticleManager(sf::RenderWindow* window, GameManager* gameManager);
    ~ParticleManager();
    void CreateParticles(int number);
    void render();
    void Update(float dt);
    void TriggerParticleExplosion(sf::Vector2f pos);

private:
    std::vector<Particle*> particles;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
};

