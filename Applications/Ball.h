//
// Created by julie on 08/05/2025.
//

#ifndef BALL_H
#define BALL_H


class Ball {
    public:
        int x1;
        int y1;
        int dx;
        int dy;
    
        Ball(int x1, int y1, int dx = 1, int dy = -1)
            : x1(x1), y1(y1), dx(dx), dy(dy) {}
    
        void move();
    };
    


#endif //BALL_H
