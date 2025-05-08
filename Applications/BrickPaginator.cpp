#include "BrickPaginator.h"
#include "../sextant/memoire/pagination/Pagination.h"
#include "../sextant/vga/vga.h"

BrickPaginator* BrickPaginator::instance = nullptr;

BrickPaginator& BrickPaginator::getInstance() {
    if (!instance) {
        Pagination* pagination = new Pagination();
        instance = new BrickPaginator(pagination, 5);
    }
    return *instance;
}

sextant_ret_t BrickPaginator::addBrickLine(Brick* line, int brickCount) {
    if (brickCount > MAX_BRICKS_PER_LINE) {
        return -SEXTANT_ERROR; 
    }

    vaddr_t vaddr = pagination->paging_map((paddr_t)line, (vaddr_t)(totalLines), false, VM_MAP_PROT_WRITE);
    if (vaddr == (vaddr_t)NULL) {
        return -SEXTANT_ERROR; 
    }

    totalLines++;
    return SEXTANT_OK;
}

Brick* BrickPaginator::createBrick(int x, int y) {
    Brick* brick = new Brick(x, y);
    return brick;
}

Brick** BrickPaginator::getCurrentPage() {
    if (currentPage) {
        return currentPage;
    }

    int startLine = currentPageIndex * linesPerPage;
    int endLine = startLine + linesPerPage;

    if (endLine > totalLines) {
        endLine = totalLines;
    }

    currentPage = new Brick*[endLine - startLine];
    for (int i = startLine; i < endLine; ++i) {
        currentPage[i - startLine] = createBrick(155, 155); // Example coordinates
    }
    return currentPage;
}

void BrickPaginator::nextPage() {
    if (currentPageIndex < (totalLines / linesPerPage) - 1) {
        currentPageIndex++;
    }
    else {
        currentPageIndex = 0; // Loop back to the first page
    }
    delete[] currentPage;
    currentPage = nullptr;
}

void BrickPaginator::previousPage() {
    if (currentPageIndex > 0) {
        currentPageIndex--;
    }
    else {
        currentPageIndex = (totalLines / linesPerPage) - 1; // Loop back to the last page
    }
    delete[] currentPage;
    currentPage = nullptr;
}

int BrickPaginator::getCurrentPageIndex() const {
    return currentPageIndex;
}

void BrickPaginator::drawCurrentPage() {
    int lineCount;
    Brick** currentPageBricks = getCurrentPage();
    if (currentPageBricks) {
        for (int i = 0; i < lineCount; ++i) {
            if (currentPageBricks[i]->status){
                draw_sprite(currentPageBricks[i]->sprite, currentPageBricks[i]->x, currentPageBricks[i]->y, 
                    currentPageBricks[i]->spriteWidth, currentPageBricks[i]->spriteHeight);
            } 
        }
    }
}