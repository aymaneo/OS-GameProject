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

Brick* BrickPaginator::getCurrentPage(int& lineCount) {
    int start = currentPage * linesPerPage;
    if (start >= totalLines) {
        lineCount = 0;
        return nullptr;
    }

    lineCount = linesPerPage;
    return (Brick*)(start * PAGE_SIZE);
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