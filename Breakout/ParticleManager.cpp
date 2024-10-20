#include "ParticleManager.h"
#include "GameManager.h"

ParticleManager::ParticleManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{

}

ParticleManager::~ParticleManager() {

}

#include <iostream>
using namespace std;

void ParticleManager::CreateParticles(int number)
{
    // Directly use the vector without dynamic allocation
    for (int i = 0; i < number; i++) {
        particles.emplace_back(new Particle(200, 200, 100));    // Add particle to the vector
    }

    // Optional: Check if particles were added
    std::cout << "Number of particles: " << particles.size() << std::endl;
   
}

void ParticleManager::render()
{
    //if()

    for (auto& particle : particles) {
        particle->render(*_window);
    }
}