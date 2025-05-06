#ifndef BRICK_PAGINATOR_H
#define BRICK_PAGINATOR_H

#include "../sextant/memoire/pagination/Pagination.h"

#define MAX_BRICKS_PER_LINE 50 

struct Brick {
    int x, y; 
    bool isActive;
};

class BrickPaginator {
private:
    Pagination* pagination; 
    int totalLines; 
    int currentPage; 
    int linesPerPage; 

public:
    BrickPaginator(Pagination* pagination, int linesPerPage);

    sextant_ret_t addBrickLine(Brick* line, int brickCount);
    Brick* getCurrentPage(int& lineCount);
    void nextPage();
    void previousPage();
    int getCurrentPageIndex() const;
};

#endif