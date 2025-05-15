// memoire.cpp
#include "./pagination/MemoirePhysique.h"
#include "Memoire.h"

// Simple byte-wise memory set since <cstring> is not allowed
static void memzero(void* ptr, size_t count) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < count; ++i) {
        p[i] = 0;
    }
}

// Physical memory manager (simple bitmap + refcount)
class PhysMem {
public:
    static const size_t PAGE_SIZE = (4*1024);
    static const size_t RAM_SIZE = 1ULL << 30; // 1 GiB
    static const size_t NUM_PAGES = RAM_SIZE / PAGE_SIZE;

    struct PageInfo { bool free; unsigned refcount; };
    static PageInfo pages[NUM_PAGES];

    static void init() {
        for (size_t i = 0; i < NUM_PAGES; ++i) {
            pages[i].free = true;
            pages[i].refcount = 0;
        }
    }

    static int alloc_frame(size_t &out_index) {
        for (size_t i = 0; i < NUM_PAGES; ++i) {
            if (pages[i].free) {
                pages[i].free = false;
                pages[i].refcount = 1;
                out_index = i;
                return 0;
            }
        }
        return -1;
    }

    static int ref_frame(size_t index) {
        if (index >= NUM_PAGES) return -1;
        pages[index].refcount++;
        return 0;
    }

    static int deref_frame(size_t index) {
        if (index >= NUM_PAGES) return -1;
        if (pages[index].refcount == 0) {
            return -1;
        }
        pages[index].refcount--;
        if (pages[index].refcount == 0) {
            pages[index].free = true;
        }
        return 0;
    }
};

PhysMem::PageInfo PhysMem::pages[PhysMem::NUM_PAGES];

// Page table entry structs
struct x86_pte { unsigned present:1, write:1, user:1, paddr:20; };
struct x86_pde { unsigned present:1, write:1, user:1, pt_paddr:20; };

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

// Implementation of memoire
memoire::memoire() {}

void memoire::mem_setup(void *begin, int size, Ecran *ec) {
    (void)begin; (void)size; (void)ec;
    paging.init();
}

vaddr_t memoire::malloc(size_t taille) {
    size_t npages = (taille + PhysMem::PAGE_SIZE - 1) / PhysMem::PAGE_SIZE;
    static vaddr_t next_free = 0x400000;
    vaddr_t va = next_free;

    for (size_t i = 0; i < npages; ++i) {
        size_t phys_idx;
        if (PhysMem::alloc_frame(phys_idx) != 0) return 0;
        paging.map(va + i * PhysMem::PAGE_SIZE, phys_idx * PhysMem::PAGE_SIZE);
    }
    next_free += npages * PhysMem::PAGE_SIZE;
    return va;
}

sextant_ret_t memoire::free(vaddr_t addr) {
    unsigned pd_idx = (addr >> PAGE_SHIFT) & 0x3FF;
    unsigned pt_idx = (addr >> PAGE_SHIFT) & 0x3FF;
    x86_pde &pd_e = paging.page_directory[pd_idx];
    if (!pd_e.present) return -1;
    x86_pte *pt = (x86_pte*)(pd_e.pt_paddr * PhysMem::PAGE_SIZE);
    if (!pt[pt_idx].present) return -1;
    size_t phys_idx = pt[pt_idx].paddr;
    pt[pt_idx].present = 0;
    PhysMem::deref_frame(phys_idx);
    return SEXTANT_OK;
}

void memoire::memoireaffiche(Ecran *ec) {
    int free_count = 0;
    for (size_t i = 0; i < PhysMem::NUM_PAGES; ++i) {
        if (PhysMem::pages[i].free) ++free_count;
    }
}

void memoire::test() {
    vaddr_t a = malloc(10000);
    if (a == 0) return;
    free(a);
}

memoire* memoire::nouveau() {
    static memoire instance;
    return &instance;
}

void* operator new(size_t taille) {
    return (void*)memoire::nouveau()->malloc(taille);
}

void operator delete(void* ptr) {
    memoire::nouveau()->free((vaddr_t)ptr);
}
