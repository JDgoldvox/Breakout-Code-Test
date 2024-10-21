#pragma once
#include <SFML/Graphics.hpp>

class GameManager;

class CameraShakeManager
{
public:
	CameraShakeManager(GameManager* gameManagerIn);
	~CameraShakeManager();

    void SetOriginalView(sf::View originalViewIn) { originalView = originalViewIn; }
    void EnableScreenShake();
	void Update(float dt);
private:
	GameManager* gameManager;

    int shakeIntervalNumber = 0;
    int shakeNumber = 0;
    bool screenShake = false;
    float shakeMoveTimer = 0;
    float shakeMoveCooldown = 0.01;
    bool isShakeMovingLeft = true;
    sf::View originalView;
};

