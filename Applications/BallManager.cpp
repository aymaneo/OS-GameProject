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

bool BallManager::addBall(int x, int y, int dx = 1, int dy = -1) {
    //TODO should add to the first null value
    if (ballCount >= MAX_BALLS) return false;
    balls[ballCount++] = new Ball(x, y, dx, dy);
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

int BallManager::getX(int index){
    if (index < 0 || index >= ballCount) return -1;
    mumuL[index].lock();
    int x = balls[index]->getX();
    mumuL[index].unlock();
    return x;
}
int BallManager::getY(int index){
    if (index < 0 || index >= ballCount) return -1;
    mumuL[index].lock();
    int y = balls[index]->getY();
    mumuL[index].unlock();
    return y;
}
void BallManager::move(int index){
    if (index < 0 || index >= ballCount) return;
    mumuL[index].lock();
    balls[index]->move();
    mumuL[index].unlock();
}