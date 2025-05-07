#pragma once
#include "Balle.h"

static const int MAX_BALLS = 10;

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
    int getCount() const { return count; }
    Balle* getBalle(int i) const { return balles[i]; }
};
