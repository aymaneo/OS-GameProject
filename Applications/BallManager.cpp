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
    mutex_liste[index].lock();
    int x = balls[index]->getX();
    mutex_liste[index].unlock();
    return x;
}
int BallManager::getY(int index){
    if (index < 0 || index >= ballCount) return -1;
    mutex_liste[index].lock();
    int y = balls[index]->getY();
    mutex_liste[index].unlock();
    return y;
}
void BallManager::moveBall(int index){
    if (index < 0 || index >= ballCount) return;
    mutex_liste[index].lock();
    balls[index]->move();
    mutex_liste[index].unlock();
}


void BallManager::removeBall(Ball* ball) {
    for (int i = 0; i < ballCount; ++i) {
        if (balls[i] == ball) {
            mutex_liste[i].lock();
            delete balls[i];
            balls[i] = nullptr;
            mutex_liste[i].unlock();
        }
    }

    // intentionnaly not shifting the array, so that when count get to its max it stop spwning balls 
    /*for (int i = index; i < ballCount - 1; ++i) {
        balls[i] = balls[i + 1];
    }*/
    //balls[--ballCount] = nullptr;
    
}