/*
 * MemoireTab.cpp
 *
 *  Created on: 30 oct. 2008
 *      Author: menaud
 */

#define DEBUG_MEMOIRETAB 0
#define BIOS_N_VIDEO_START 0xa0000
#define BIOS_N_VIDEO_END   0x100000

#include "MemoireTab.h"
#define ALIGN_INF(val,boundary) (((unsigned)(val)) & (~((boundary)-1)))
/** Align on a boundary (MUST be a power of 2), so that return value >= val */
#define ALIGN_SUP(val,boundary) ({ unsigned int __bnd=(boundary); (((((unsigned)(val))-1) & (~(__bnd - 1))) + __bnd); })

#define PAGE_ALIGN_INF(val) ALIGN_INF((val), PAGE_SIZE)
#define PAGE_ALIGN_SUP(val) ALIGN_SUP((val), PAGE_SIZE)

extern char __b_kernel, __e_kernel;
paddr_t kernel_core_base,kernel_core_top;

struct bloc {
	int cpt;
	bool isFree;
};

#define PAGE_SIZE 4096
#define MAXMEM 3000

bloc TabPages[MAXMEM];

void MemoireTab::memoireaffiche(Ecran *ec){
// ???
}


void MemoireTab::mem_setup(void * begin, int size,Ecran *ecran) {
	debut=begin;
	taille=size;
	ec=ecran;
}

vaddr_t MemoireTab::malloc(size_t nbytes){
	for (int i=0;i<(MAXMEM);i++) {
		if (TabPages[i].isFree==true) {
			TabPages[i].isFree=false;
			i = (vaddr_t)((char*)debut + i * PAGE_SIZE);
			return (vaddr_t) i;
		}
	}
}



sextant_ret_t MemoireTab::free(vaddr_t addr) {
	vaddr_t addr_r = (char*)addr - (char*)debut;

	if (TabPages[addr_r/PAGE_SIZE].isFree==false) {
			TabPages[addr_r/PAGE_SIZE].isFree=true;
	}
	return SEXTANT_OK;
}


