#pragma once
#include <vector>
#include "Particle.h"
#include <SFML/Graphics.hpp>

using std::vector;


class GameManager;

class ParticleManager
{
public:
    ParticleManager(sf::RenderWindow* window, GameManager* gameManager);
    ~ParticleManager();
    void CreateParticles(int number);
    void render();

private:
    std::vector<Particle*> particles;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
};

