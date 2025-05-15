#include "../Memoire.h"
#include "./Pagination.h"

class Paging {
public:
    x86_pde *page_directory;

    void init() {
        PhysMem::init();
        // allocate PD frame
        size_t idx;
        if (PhysMem::alloc_frame(idx) != 0) return;
        page_directory = (x86_pde*)(idx * PhysMem::PAGE_SIZE);
        memzero(page_directory, PhysMem::PAGE_SIZE);
    }

    int map(vaddr_t vaddr, paddr_t paddr) {
        unsigned pd_idx = (vaddr >> PAGE_SHIFT) & 0x3FF;
        unsigned pt_idx = (vaddr >> PAGE_SHIFT) & 0x3FF;

        x86_pde &pd_e = page_directory[pd_idx];
        x86_pte *pt;

        if (!pd_e.present) {
            size_t new_idx;
            if (PhysMem::alloc_frame(new_idx) != 0) return -1;
            pt = (x86_pte*)(new_idx * PhysMem::PAGE_SIZE);
            memzero(pt, PhysMem::PAGE_SIZE);
            pd_e.present = 1;
            pd_e.write = 1;
            pd_e.pt_paddr = (unsigned)new_idx;
        } else {
            pt = (x86_pte*)(pd_e.pt_paddr * PhysMem::PAGE_SIZE);
            PhysMem::ref_frame(pd_e.pt_paddr);
        }

        pt[pt_idx].present = 1;
        pt[pt_idx].write = 1;
        pt[pt_idx].user = 0;
        pt[pt_idx].paddr = (unsigned)(paddr >> PAGE_SHIFT);
        return 0;
    }
};

// Single Paging instance
static Paging paging;