#pragma once

class Platform {
public:
    int static size;
    int x;
    int y;
    Platform(int x, int y) : x(x), y(y) {}
    void moveLeft();
    void moveRight();
};
