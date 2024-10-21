#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include "ParticleManager.h"

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager, ParticleManager* particleManagerIn);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    ParticleManager* particleManager;
    static constexpr float TOP_PADDING = 100.0f;
};
