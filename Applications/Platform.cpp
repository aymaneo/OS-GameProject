#include "Platform.h"

void Platform::moveLeft() {
    x = x - speed;
}

void Platform::moveRight() {
    x = x + speed;
}
