#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    particleManager = new ParticleManager(_window, this);

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this, particleManager);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

    //create pool of particles
    particleManager->CreateParticles(30 * 8);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;

    //for shake
    originalView = getWindow()->getView();

    if (_lives <= 0)
    {
        UpdateScreenShake(dt); //shake screen when we lost
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);

    particleManager->Update(dt);
    UpdateScreenShake(dt);
}

void GameManager::loseLife(float dt)
{
    _lives--;
    _ui->lifeLost(_lives);

    //screen shake
    screenShake = true;
}

void GameManager::render()
{
    particleManager->render();
    _paddle->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ball->render();
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }

void GameManager::UpdateScreenShake(float dt) {
    
   //no screen shake = return
    if (!screenShake) {
        return;
    }
    
    //limit number of shakes
    if (shakeNumber == 3) {
        shakeNumber = 0;
        screenShake = false;
        getWindow()->setView(originalView);
        return;
    }
   
    //check if dt has reached value
    if (shakeMoveTimer > 0)
    {
        shakeMoveTimer -= dt;
        return;
    }
    else {
        shakeMoveTimer = shakeMoveCooldown;
    }

    //reset shake intervals and change direction
    if (shakeIntervalNumber > 10) {
        shakeIntervalNumber = 0;
        isShakeMovingLeft = !isShakeMovingLeft;
        shakeNumber++;
    }

    auto win = getWindow();
    auto view = win->getView();

    if (isShakeMovingLeft) {
        view.move(2, 0.5);
        win->setView(view);
    }
    else {
        view.move(-2, -0.5);
        win->setView(view);
    }
    
    shakeIntervalNumber++;
}
