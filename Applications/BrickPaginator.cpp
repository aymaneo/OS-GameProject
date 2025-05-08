#include "BrickPaginator.h"
#include "../sextant/memoire/pagination/Pagination.h"

BrickPaginator::BrickPaginator(Pagination* pagination, int linesPerPage)
    : pagination(pagination), totalLines(0), currentPage(0), linesPerPage(linesPerPage) {}

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

Brick BrickPaginator::getBrick(int x, int y){
    return Brick(x, y);
}

Brick* BrickPaginator::getCurrentPage() {
    int startLine = currentPage * linesPerPage;
    int endLine = startLine + linesPerPage;
    if (endLine > totalLines) {
        endLine = totalLines;
    }

    Brick* pageBricks = new Brick[endLine - startLine];
    for (int i = startLine; i < endLine; ++i) {
        pageBricks[i - startLine] = getBrick(i % MAX_BRICKS_PER_LINE, i / MAX_BRICKS_PER_LINE);
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
    Brick* currentPageBricks = getCurrentPage();
    if (currentPageBricks) {
        for (int i = 0; i < lineCount; ++i) {
            currentPageBricks[i].draw();
        }
    }
}