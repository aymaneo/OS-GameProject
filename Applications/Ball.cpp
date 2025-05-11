//
// Created by julie on 08/05/2025.
//

#include "Ball.h"

#include "BallManager.h"

void Ball::move() {
    int ctr_x = getX() + BALL_WIDTH/2;
    int ctr_y = getY() + BALL_HEIGHT/2;
    if (CollisionManager::isColliding(ctr_x + dx, ctr_y + dy)) {
        if(CollisionManager::isColliding(ctr_x + dx, ctr_y)) dx = -dx;
        if(CollisionManager::isColliding(ctr_x, ctr_y + dy)) dy = -dy;
        // Act now to apply the collision, if it collides on both x and y
    }
    
    x += dx;
    y += dy;
}

int Ball::getX() {
    return x;
}

int Ball::getY() {
    return y;
}