#pragma once


class Platform {
public:
    int x;
    int y;
    Platform(int x, int y) : x(x), y(y) {}
    void moveLeft();
    void moveRight();
};
