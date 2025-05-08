#pragma once

#include "../sextant/memoire/pagination/Pagination.h"
#include "Brick.h"

#define MAX_BRICKS_PER_LINE 5

class BrickPaginator {
private:
    static BrickPaginator* instance;
    Pagination* pagination; 
    int totalLines; 
    Brick** currentPage;
    int currentPageIndex; 
    int linesPerPage; 

    BrickPaginator(Pagination* pagination, int linesPerPage) 
        : pagination(pagination), totalLines(0), currentPage(0), linesPerPage(linesPerPage) {};

public:

    static BrickPaginator& getInstance();
    sextant_ret_t addBrickLine(Brick* line, int brickCount);
    Brick** getCurrentPage();
    Brick* createBrick(int x, int y);
    void nextPage();
    void previousPage();
    int getCurrentPageIndex() const;
    void drawCurrentPage();
};