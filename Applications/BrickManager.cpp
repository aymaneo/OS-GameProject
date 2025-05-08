#include <Applications/BrickManager.h>

BrickManager* BrickManager::instance = nullptr;

BrickManager& BrickManager::getInstance() {
    if (!instance) {
        instance = new BrickManager();
    }

    for (int i = 0; i < 15; ++i) {
        instance->bricks[i] = Brick();
        instance->brickCount ++;
    }

    return *instance;  
}

BrickManager::~BrickManager() {
    delete instance;
}

int BrickManager::getBrickCount() {
    return brickCount;
}