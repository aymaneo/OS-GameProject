//
// Created by julie on 08/05/2025.
//

#include "Ball.h"

void Ball::move() {
    auto isEnclosedX = [](int x) -> bool  {return (x > 1 && x < 319);};
    auto isEnclosedY = [](int y) -> bool  {return (y > 1 && y < 199);};
    
    
    if (!isEnclosedX(x1)) dx = -dx;
    if (!isEnclosedY(y1)) dy = -dy;
    
    //TODO handle collision

    


    x1 += dx;
    y1 += dy;

}