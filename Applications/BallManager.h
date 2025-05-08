//
// Created by julie on 08/05/2025.
//

#include "Ball.h"
#ifndef BALLMANAGER_H
#define BALLMANAGER_H

class BallManager {
private:

    static BallManager* instance2;
    Ball ball1;
    BallManager() : ball1(130, 130) {}

public:
    static BallManager& getInstance2();
    ~BallManager();

    Ball& getBall1();
};



#endif //BALLMANAGER_H
