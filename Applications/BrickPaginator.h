#ifndef BRICK_PAGINATOR_H
#define BRICK_PAGINATOR_H

#include "../sextant/memoire/pagination/Pagination.h"
#include "Brick.h"

#define MAX_BRICKS_PER_LINE 50 

class BrickPaginator {
private:
    Pagination* pagination; 
    int totalLines; 
    int currentPage; 
    int linesPerPage; 

public:
    BrickPaginator(Pagination* pagination, int linesPerPage);

    sextant_ret_t addBrickLine(Brick* line, int brickCount);
    Brick* getCurrentPage();
    Brick getBrick(int x, int y);
    void nextPage();
    void previousPage();
    int getCurrentPageIndex() const;
    void drawCurrentPage();
};

#endif