#pragma once

#include <Applications/Brick.h>

#define BRICK_WIDTH  24
#define BRICK_HEIGHT 6

class BrickManager {
    private:
        static BrickManager* brick_manager_instance;
        int brickCount;

        BrickManager() : brickCount(0) {};
    public:
        Brick bricks[15];
        static const int bricksPerLine = 5;
        static BrickManager& getBricKManagerInstance(); 
        static const int brickWidth = BRICK_WIDTH;
        static const int brickHeight = BRICK_HEIGHT; 
        int getBrickCount(); 

        ~BrickManager();

        const unsigned char sprite[BRICK_WIDTH*BRICK_HEIGHT] = {
          136, 132,   1,   1,   1,   1,  96,   1,   1,   1,   1,   1,  80,   1,   1,   2,
            1,  80, 160,   1,  80,   1, 131, 135,   4, 131, 151, 134, 134, 134, 151, 134,
          134, 134, 134, 134, 150, 134, 134, 134, 134, 150, 151, 134, 150, 134,   5, 133,
          160, 117, 153, 136, 136, 152, 152, 136, 152, 136, 153, 136, 136, 153, 136, 152,
          136, 135, 152, 136, 136, 136, 133,   2,   2,   4, 134, 133, 134, 116, 150, 118,
          134, 133, 134, 133, 134, 133, 134, 133, 134, 133, 134, 133, 134, 134,   4, 160,
           96, 161,  80,   3,   2,   3,  96,   3,   2,   3,   2,   3,   2,   3,   2,   3,
            2,   3,   3,   2,   3, 144,   2,   2,   3,   3, 160,  80, 160,   2, 161,   2,
          144,   2, 144,   1, 144,  80, 160, 144,   2, 144,  80, 160,   2,  80, 160,   2
          };
};