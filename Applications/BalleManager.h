#pragma once
#include "Balle.h"

#define MAX_BALLS 10

class BalleManager
{
private:
    static BalleManager *instance;
    Balle *balles[MAX_BALLS];
    int count;
    BalleManager();

public:
    static BalleManager &getInstance();
    void spawnBall(int x, int y);
    void update();
};
