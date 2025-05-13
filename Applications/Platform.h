#pragma once


class Platform {
private:
    static const int speed = 3;
    int x;
    int y;
    friend class PlatformManager;
    void moveLeft();
    void moveRight();
public:
    Platform(int x, int y) : x(x), y(y) {}
};
