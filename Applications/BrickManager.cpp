#include <Applications/BrickManager.h>

BrickManager* BrickManager::brick_manager_instance = nullptr;

BrickManager& BrickManager::getBricKManagerInstance() {
    if (!brick_manager_instance) {
        brick_manager_instance = new BrickManager();
    }

    if (brick_manager_instance->brickCount == 0) {
        brick_manager_instance->generateBricks();
    }
    return *brick_manager_instance;
}

BrickManager::~BrickManager() {
    delete brick_manager_instance;
}

int BrickManager::getBrickCount() {
    return brickCount;
}

void BrickManager::generateBricks(){
    int space_x = 0;
    int space_y = 3;
    int padding = 4;

    int number_of_lines = 4;

    int cruseur_x = 0; 
    int curseur_y = 3;
    for (int j = 0; j < number_of_lines; j++){
        cruseur_x = padding;
        for (int i = 0; i < bricksPerLine; i++){
            brick_manager_instance->bricks[j * bricksPerLine + i].x = cruseur_x;
            brick_manager_instance->bricks[j * bricksPerLine + i].y = curseur_y;
            cruseur_x += BrickManager::brickWidth + space_x;
            brickCount++;
        }
        curseur_y += BrickManager::brickHeight;
    } 
}