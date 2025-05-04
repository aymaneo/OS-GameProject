#pragma once

#include "Platform.h"

class PlatformManager {
private:
    static PlatformManager* instance;
    Platform platform1;
    Platform platform2;

    PlatformManager() : platform1(5, 10), platform2(10, 20) {}

public:
    static PlatformManager& getInstance();
    ~PlatformManager();

    Platform& getPlatform1();
    Platform& getPlatform2();
};
