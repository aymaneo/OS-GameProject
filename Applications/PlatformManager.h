#pragma once

#include "Platform.h"

class PlatformManager {
private:
    static PlatformManager* instance;
    Platform platform1;
    Platform platform2;

    PlatformManager() : platform1(150, 150), platform2(100, 100) {}

public:
    static PlatformManager& getInstance();
    ~PlatformManager();

    Platform& getPlatform1();
    Platform& getPlatform2();
};
