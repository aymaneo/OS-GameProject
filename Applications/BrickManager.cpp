#include <Applications/BrickManager.h>

BrickManager* BrickManager::brick_manager_instance = nullptr;

BrickManager& BrickManager::getBricKManagerInstance() {
    if (!brick_manager_instance) {
        brick_manager_instance = new BrickManager();
    }

    for (int i = 0; i < 15; ++i) {
        brick_manager_instance->bricks[i] = Brick();
        brick_manager_instance->brickCount ++;
    }

    return *brick_manager_instance;  
}

BrickManager::~BrickManager() {
    delete brick_manager_instance;
}

int BrickManager::getBrickCount() {
    return brickCount;
}