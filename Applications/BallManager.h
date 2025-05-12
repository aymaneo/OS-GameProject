//
// Created by julie on 08/05/2025.
//

#include "Ball.h"
#include <sextant/Synchronisation/Mutex/Mutex.h>
#ifndef BALLMANAGER_H
#define BALLMANAGER_H
#define MAX_BALLS 20
#define BALL_WIDTH  8
#define BALL_HEIGHT 8


class BallManager {
private:
    static BallManager* instance;
    Ball* balls[MAX_BALLS];
    int ballCount;
    BallManager();
    Mutex mutex_liste[MAX_BALLS];

public:
  unsigned char ball_sprite[BALL_WIDTH*BALL_HEIGHT] = 
  {
      153, 153,   2,   2,   2,   2, 153, 218, 170, 161,  99, 135, 135, 115,   3, 218,
        2,   5, 135, 170, 170, 151,   5, 144,   2, 115, 153, 153, 153, 153, 115,   2,
        2,   5, 135, 152, 153, 134,   5, 161,   2, 145, 115, 135, 135, 148,   2,   2,
      170,   2,   3,   2,   2,   2,  80, 219, 170, 170, 161,   2,   3,  96, 153, 218
      };
    static BallManager& getInstance();
    ~BallManager();

    Ball* getBall(int index);
    bool addBall(int x, int y, int dx, int dy);  
    int getBallCount() const;
    void getAllBalls(Ball **outArray, int maxSize, int &outCount);
    void removeBall(int ball);
    void moveBall(int index);
    int getX(int index);
    int getY(int index);
    void move(int index);
};

#endif //BALLMANAGER_H
