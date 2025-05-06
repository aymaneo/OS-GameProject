#include "Balle.h"
#include "../sextant/vga/vga.h"

Balle::Balle(int x, int y, int dx, int dy) : x(x), y(y), dx(dx), dy(dy) {}

void Balle::move()
{
    clear();
    x += dx;
    y += dy;

    // Simple bounce for testing, EN ATTENDANT LE COLISION MANGER
    if (x <= 0 || x >= 320)
        dx = -dx;
    if (y <= 0 || y >= 200)
        dy = -dy;

    draw();
}

void Balle::draw()
{
    plot_square(x, y, 2, 15);
}

void Balle::clear()
{
    plot_square(x, y, 2, 0);
}
