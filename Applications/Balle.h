#pragma once

class Balle
{
public:
    int x, y;
    int dx, dy;

    Balle(int x, int y, int dx = 1, int dy = -1);
    void move();
    void draw();
    void clear();
};
