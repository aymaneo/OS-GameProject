//
// Created by julie on 08/05/2025.
//

#include "BallManager.h"

BallManager* BallManager::instance2 = nullptr;

BallManager& BallManager::getInstance2() {
    if (!instance2) {
        instance2 = new BallManager();
    }
    return *instance2;
}

BallManager::~BallManager() {
    delete instance2;
}

Ball& BallManager::getBall1() {
    return ball1;
}
