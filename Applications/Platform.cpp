#include "Platform.h"

void Platform::moveLeft() {
    x -= speed;
    // science BBY
    if (x > 320 || x < 0) {
        x = (x % 320 + 320) % 320;
    }
}

void Platform::moveRight() {
    x += speed;
    // science BBY
    if (x > 320 || x < 0) {
        x = (x % 320 + 320) % 320;
    }
    
    
}
