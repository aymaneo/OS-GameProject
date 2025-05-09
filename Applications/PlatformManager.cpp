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

Platform& PlatformManager::getPlatform1() { 
    return platform1; 
}

Platform& PlatformManager::getPlatform2() { 
    return platform2; 
}

Platform& PlatformManager::getEnnemy_platform(){
    return ennemy_platform;
};

