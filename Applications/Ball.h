//
// Created by julie on 08/05/2025.
//

#ifndef BALL_H
#define BALL_H

#include <sextant/Synchronisation/Mutex/Mutex.h>

class Ball {
private:
    int x;
    int y;
    int dx;
    int dy;

public:
    Ball(int x, int y, int dx = 1, int dy = -1)
        : x(x), y(y), dx(dx), dy(dy) {}

    void move();
    int getX();
    int getY();
};


#endif //BALL_H
