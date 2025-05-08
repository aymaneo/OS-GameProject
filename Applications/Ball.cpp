//
// Created by julie on 08/05/2025.
//

#include "Ball.h"

void Ball::move() {
    const int min_val = 10;
    const int max_val = 190;

    if (!(x1 >= min_val && x1 <= max_val && y1 >= min_val && y1 <= max_val)) {
        if (x1 < min_val || x1 > max_val) dx = -dx;
        if (y1 < min_val || y1 > min_val) dy = -dy;  
    } 
    //TODO handle collision 
    x1 += dx;
    y1 += dy;

}