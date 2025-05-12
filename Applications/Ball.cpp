//
// Created by julie on 08/05/2025.
//

#include "Ball.h"

#include "BallManager.h"

void Ball::move() {
    int ctr_x = getX() + BALL_WIDTH/2;
    int ctr_y = getY() + BALL_HEIGHT/2;
    int temp_x = ctr_x + dx;
    int temp_y = ctr_y + dy;

    if (CollisionManager::isColliding(temp_x, temp_y)) {
        if (CollisionManager::isColliding(temp_x, ctr_y)) dx = -dx;
        if (CollisionManager::isColliding(ctr_x, temp_y)) dy = -dy;
        // Act now to apply the collision, if it collides on both x and y
        CollisionManager::applyCollision(temp_x, temp_y);
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