#include "Platform.h"

int Platform::size = 5;

void Platform::moveLeft() {
    this->x += -1;
}

void Platform::moveRight() {
    this->x += 1;
}
