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

    vaddr_t vaddr = pagination->paging_map((paddr_t)line, (vaddr_t)(totalLines * PAGE_SIZE), false, VM_MAP_PROT_WRITE);
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
    int startLine = currentPage * linesPerPage;
    int endLine = startLine + linesPerPage;
    if (endLine > totalLines) {
        endLine = totalLines;
    }

    Brick* pageBricks[endLine - startLine];
    for (int i = startLine; i < endLine; ++i) {
        pageBricks[i - startLine] = createBrick(i * 10, i * 10);
    }

    return pageBricks;
}

void BrickPaginator::nextPage() {
    if ((currentPage + 1) * linesPerPage < totalLines) {
        currentPage++;
    }
}

void BrickPaginator::previousPage() {
    if (currentPage > 0) {
        currentPage--;
    }
}

int BrickPaginator::getCurrentPageIndex() const {
    return currentPage;
}

void BrickPaginator::drawCurrentPage() {
    int lineCount;
    Brick** currentPageBricks = getCurrentPage();
    if (currentPageBricks) {
        for (int i = 0; i < lineCount; ++i) {
            draw_sprite(currentPageBricks[i]->sprite, currentPageBricks[i]->x, currentPageBricks[i]->y, 
                        currentPageBricks[i]->spriteWidth, currentPageBricks[i]->spriteHeight);
        }
    }
}