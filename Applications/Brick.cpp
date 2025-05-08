#include "Applications/Brick.h"

Brick::Brick() : status(true) {}

void Brick::changeStatus() {
    status = !status;
}