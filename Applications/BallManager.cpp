//
// Created by julie on 08/05/2025.
//

#include "BallManager.h"

BallManager* BallManager::instance = nullptr;
BallManager::BallManager() : ballCount(0) {
    for (int i = 0; i < MAX_BALLS; ++i) {
        balls[i] = nullptr;
    }
}

BallManager& BallManager::getInstance() {
    if (!instance) {
        instance = new BallManager();
    }
    return *instance;
}

BallManager::~BallManager() {
    for (int i = 0; i < MAX_BALLS; ++i) {
        delete balls[i];
    }
    delete instance;
}

bool BallManager::addBall(int x, int y) {
    //TODO should add to the first null value
    if (ballCount >= MAX_BALLS) return false;
    balls[ballCount++] = new Ball(x, y);
    return true;
}

Ball* BallManager::getBall(int index) {
    if (index < 0 || index >= ballCount) return nullptr;
    return balls[index];
}

int BallManager::getBallCount() const {
    return ballCount;
}

void BallManager::getAllBalls(Ball** outArray, int maxSize, int& outCount) {
    outCount = (ballCount < maxSize) ? ballCount : maxSize;
    for (int i = 0; i < outCount; ++i) {
        outArray[i] = balls[i];
    }
}