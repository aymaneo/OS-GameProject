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
    int x = platform1.x;
    return x;
}
int PlatformManager::getPlatform1Y() {
    int y = platform1.y;
    return y;
}
void PlatformManager::movePlatform1Left() {
    platform1.moveLeft();
}
void PlatformManager::movePlatform1Right() {
    platform1.moveRight();
}
int PlatformManager::getPlatform2X() {
    int x = platform2.x;
    return x;
}
int PlatformManager::getPlatform2Y() {
    int y = platform2.y;
    return y;
}
void PlatformManager::movePlatform2Left() {
    platform2.moveLeft();
}
void PlatformManager::movePlatform2Right() {
    platform2.moveRight();
}
int PlatformManager::getEnnemy_platformX() {
    int x = ennemy_platform.x;
    return x;
}

int PlatformManager::getEnnemy_platformY() {
    int y = ennemy_platform.y;
    return y;
}

void PlatformManager::moveEnnemy_platformLeft() {
    ennemy_platform.moveLeft();
}

void PlatformManager::moveEnnemy_platformRight() {
    ennemy_platform.moveRight();
}
