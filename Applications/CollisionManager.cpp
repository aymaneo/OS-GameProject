//
// Created by julie on 11/05/2025.
//

#include "CollisionManager.h"
#include "PlatformManager.h"
#include "BrickManager.h"

bool CollisionManager::isInsideRectangle(int x, int y, int rect_x, int rect_y, int rect_width, int rect_height) {
        return (x >= rect_x && x <= rect_x + rect_width && y >= rect_y && y <= rect_y + rect_height);
} 

bool CollisionManager::applyCollision(int pos_x,int pos_y){
    return isColliding(pos_x, pos_y);
}

bool CollisionManager::isColliding(int pos_x, int pos_y){
    // test if position is wall
    if (pos_x < 3 || pos_x > 317) return true;
    // test if position is roof
    if (pos_y < 3) return true;

    // test if position is platform
    if (isInsideRectangle(pos_x, pos_y, 
                        PlatformManager::getInstance().getPlatform1X(), PlatformManager::getInstance().getPlatform1Y(), 
                        PLATFORM_WIDTH, PLATFORM_HEIGHT)) {
        return true;
    }
    if (isInsideRectangle(pos_x, pos_y, 
                        PlatformManager::getInstance().getPlatform2X(), PlatformManager::getInstance().getPlatform2Y(), 
                        PLATFORM_WIDTH, PLATFORM_HEIGHT)) {
        return true;
    }
    if (isInsideRectangle(pos_x, pos_y, 
                        PlatformManager::getInstance().getEnnemy_platformX(), PlatformManager::getInstance().getEnnemy_platformY(), 
                        PLATFORM_WIDTH, PLATFORM_HEIGHT)) {
        return true;
    }
    
    // test if position is brick
    for (int i = 0; i < BrickManager::getInstance().getBrickCount(); i++){
        if (isInsideRectangle(pos_x, pos_y, 
                                BrickManager::getInstance().bricks[i].x, BrickManager::getInstance().bricks[i].y, 
                                BrickManager::getInstance().brickWidth, BrickManager::getInstance().brickHeight)
                && BrickManager::getInstance().bricks[i].status) {
            return true;
        }    
    }
    
    return false;
}