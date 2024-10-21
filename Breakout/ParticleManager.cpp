#include "ParticleManager.h"
#include "GameManager.h"

ParticleManager::ParticleManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{

}

ParticleManager::~ParticleManager() {
    for (auto element : particles) {
        delete element;
    }
}

void ParticleManager::CreateParticles(int number)
{
    for (int i = 0; i < number; i++) {
        particles.emplace_back(new Particle(200, 200, 1));    // Add particle to the vector
    }

    std::cout << "Number of particles: " << particles.size() << std::endl;
}

void ParticleManager::render()
{
    //draw all active particles
    for (auto& particle : particles) 
    {
        if (particle->GetIsActive()) 
        {
            particle->render(*_window);
        }
    }
}

void ParticleManager::Update(float dt) {
    for (auto& particle : particles) {
        if (particle->GetIsActive())
        {
            particle->Update(dt);
        }
    }
}

void ParticleManager::TriggerParticleExplosion(sf::Vector2f pos) 
{
    int successfulParticles = 0;

    for (auto& particle : particles) {

        //ignore active particles
        if (particle->GetIsActive()) {
            continue;
        }

        particle->Explode(pos);
        successfulParticles++;

        //break if we have 10 particles
        if (successfulParticles == 30) {
            break;
        }
    }

    if (successfulParticles != 10) {
        cout << "did nothing since not enough non active particles\n";
    }
}