#include "BalleManager.h"

BalleManager *BalleManager::instance = nullptr;

BalleManager::BalleManager() : count(0) {}

BalleManager &BalleManager::getInstance()
{
    if (!instance)
        instance = new BalleManager();
    return *instance;
}

void BalleManager::spawnBall(int x, int y)
{
    if (count < MAX_BALLS)
    {
        balles[count++] = new Balle(x, y);
    }
}

void BalleManager::update()
{
    for (int i = 0; i < count; i++)
    {
        balles[i]->move();
    }
}
