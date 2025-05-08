#include "Applications/Brick.h"

Brick::Brick(int x, int y) : x(x), y(y), status(true) {}

void Brick::changeStatus() {
    status = !status;
}