#include "PlatformManager.h"

PlatformManager* PlatformManager::instance = nullptr;

PlatformManager& PlatformManager::getInstance() {
    if (!instance) {
        instance = new PlatformManager();
    }
    return *instance;
}

PlatformManager::~PlatformManager() {
    delete instance;
}

int PlatformManager::getPlatform1X() {
    mutex_platform1.P();
    int x = platform1.x;
    mutex_platform1.V();
    return x;
}
int PlatformManager::getPlatform1Y() {
    mutex_platform1.P();
    int y = platform1.y;
    mutex_platform1.V();
    return y;
}
void PlatformManager::movePlatform1Left() {
    mutex_platform1.P();
    platform1.moveLeft();
    mutex_platform1.V();
}
void PlatformManager::movePlatform1Right() {
    mutex_platform1.P();
    platform1.moveRight();
    mutex_platform1.V();
}
int PlatformManager::getPlatform2X() {
    mutex_platform2.P();
    int x = platform2.x;
    mutex_platform2.V();
    return x;
}
int PlatformManager::getPlatform2Y() {
    mutex_platform2.P();
    int y = platform2.y;
    mutex_platform2.V();
    return y;
}
void PlatformManager::movePlatform2Left() {
    mutex_platform2.P();
    platform2.moveLeft();
    mutex_platform2.V();
}
void PlatformManager::movePlatform2Right() {
    mutex_platform2.P();
    platform2.moveRight();
    mutex_platform2.V();
}
int PlatformManager::getEnnemy_platformX() {
    mutex_ennemy_platform.P();
    int x = ennemy_platform.x;
    mutex_ennemy_platform.V();
    return x;
}

int PlatformManager::getEnnemy_platformY() {
    mutex_ennemy_platform.P();
    int y = ennemy_platform.y;
    mutex_ennemy_platform.V();
    return y;
}

void PlatformManager::moveEnnemy_platformLeft() {
    mutex_ennemy_platform.P();
    ennemy_platform.moveLeft();
    mutex_ennemy_platform.V();
}

void PlatformManager::moveEnnemy_platformRight() {
    mutex_ennemy_platform.P();
    ennemy_platform.moveRight();
    mutex_ennemy_platform.V();
}
