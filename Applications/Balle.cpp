#include "Balle.h"
#include <sextant/vga/vga.h>

Balle::Balle(int x, int y, int dx, int dy)
    : x(x), y(y), dx(dx), dy(dy) {}

void Balle::move()
{
    clear();
    x += dx;
    y += dy;

    if (x < 0)
    {
        x = 0;
        dx = -dx;
    }
    else if (x > 318)
    {
        x = 318;
        dx = -dx;
    }

    if (y < 0)
    {
        y = 0;
        dy = -dy;
    }
    else if (y > 198)
    {
        y = 198;
        dy = -dy;
    }

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
