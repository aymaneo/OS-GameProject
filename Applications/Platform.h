#pragma once


class Platform {
private:
    static const int speed = 3;
public:
    int x;
    int y;
    Platform(int x, int y) : x(x), y(y) {}
    void moveLeft();
    void moveRight();
};
