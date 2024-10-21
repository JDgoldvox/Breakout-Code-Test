#include "CameraShakeManager.h"
#include "GameManager.h"

CameraShakeManager::CameraShakeManager(GameManager* gameManagerIn) :
    gameManager(gameManagerIn)
{

}

CameraShakeManager::~CameraShakeManager() {

}

void CameraShakeManager::Update(float dt) {

    //no screen shake = return
    if (!screenShake) {
        return;
    }

    //limit number of shakes
    if (shakeNumber == 3) {
        shakeNumber = 0;
        screenShake = false;
        gameManager->getWindow()->setView(originalView);
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

    auto win = gameManager->getWindow();
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

void CameraShakeManager::EnableScreenShake() 
{ 
    screenShake = true; 
}