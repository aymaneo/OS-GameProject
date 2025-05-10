//
// Created by julie on 08/05/2025.
//

#include "Ball.h"
void Ball::move() {
    auto isEnclosedX = [](int x1) -> bool  {return (x1 > 1 && x1 < 319);};
    auto isEnclosedY = [](int y1) -> bool  {return (y1 > 1 && y1 < 199);};
        
    
    if (!isEnclosedX(getX())) dx = -dx;
    if (!isEnclosedY(getY())) dy = -dy;
    
    //TODO handle collision
    x += dx;
    y += dy;
}

int Ball::getX() {
    int value = x;
    return value;
}

int Ball::getY() {
    int value = y;
    return value;
}