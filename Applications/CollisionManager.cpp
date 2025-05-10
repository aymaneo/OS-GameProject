#include "CollisionManager.h"
#include "PlatformManager.h"
#include "BrickManager.h"
#include "BallManager.h"


CollisionManager::CollisionManager()
{
}

void CollisionManager::collisionBall()
{
    BallManager ball_manager = BallManager::getInstance2();
    Ball& ball = ball_manager.getBall1();

    PlatformManager& platform_manager = PlatformManager::getInstance();
    Platform& platform1 = platform_manager.getPlatform1();
    Platform& platform2 = platform_manager.getPlatform2();
    BrickManager& brick_manager = BrickManager::getBricKManagerInstance();

    // Check collision with platform 1
    if (ball.x1 >= platform1.getX() && ball.x1 <= platform1.getX() + PlatformManager::platformWidth &&
        ball.y1 >= platform1.getY() && ball.y1 <= platform1.getY() + PlatformManager::platformHeight) {
        ball.setY(platform1.getY() - BallManager::ballHeight);
        ball.setDirection(0, -ball.getDirection().y);
    }

    // Check collision with platform 2
    if (ball.x1 >= platform2.getX() && ball.x1 <= platform2.getX() + PlatformManager::platformWidth &&
        ball.y1 >= platform2.getY() && ball.y1 <= platform2.getY() + PlatformManager::platformHeight) {
        ball.setY(platform2.getY() - BallManager::ballHeight);
        ball.setDirection(0, -ball.getDirection().y);
    }

    // Check collision with bricks
    for (int i = 0; i < BrickManager::bricksPerLine; i++) {
        Brick& brick = brick_manager.bricks[i];
        if (brick.status && ball.x1 >= brick.x && ball.x1 <= brick.x + BrickManager::brickWidth &&
            ball.y1 >= brick.y && ball.y1 <= brick.y + BrickManager::brickHeight) {
            ball.setY(brick.y - BallManager::ballHeight);
            ball.setDirection(0, -ball.getDirection().y);
            brick.changeStatus(); // Hide the brick on collision
        }
    }
    
}
