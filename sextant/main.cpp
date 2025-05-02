#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <drivers/PortSerie.h>
#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <drivers/Clavier.h>
#include <sextant/memoire/Memoire.h>
#include <sextant/ordonnancements/cpu_context.h>
#include <sextant/ordonnancements/preemptif/thread.h>
#include <sextant/types.h>
#include <sextant/Synchronisation/Spinlock/Spinlock.h>
#include <sextant/memoire/segmentation/gdt.h>
#include <sextant/memoire/Memoire.h>
#include <sextant/memoire/MemoirePion.h>
#include <sextant/memoire/pagination/MemoirePhysique.h>
#include <sextant/memoire/pagination/Pagination.h>

//#include <Applications/Entity/Entity.h>


extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom; //Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;//Taille de la pile d'exécution

Timer timer;
//paddr_t kernel_core_base,kernel_core_top;
unsigned long address;

struct cpu_state *ctxt_hello1;
struct cpu_state *ctxt_hello2;
struct cpu_state *ctxt_main;
vaddr_t hello1_stack, hello2_stack;
char tab1[4096];
char tab2[4096];
char tab[30000];

Ecran ecran;
memoire *InterfaceMemoire;
Ecran *monEcran = &ecran;

#define PAGINATION_USE 1



void Sextant_Init(){
	idt_setup();
	irq_setup();
	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);
	asm volatile("sti\n"); //Autorise les interruptions
	irq_set_routine(IRQ_KEYBOARD, handler_clavier);
	multiboot_info_t* mbi;
	mbi = (multiboot_info_t*)address;
	gdt_setup();
	InterfaceMemoire=memoire::nouveau();
	InterfaceMemoire->mem_setup(& __e_kernel,(mbi->mem_upper<<10) + (1<<20),&ecran);
	thread_subsystem_setup(bootstrap_stack_bottom,bootstrap_stack_size);
	sched_subsystem_setup();
	irq_set_routine(IRQ_TIMER, sched_clk);
}





extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Clavier clavier;
	Sextant_Init();

	ecran.effacerEcran(NOIR);

	ecran.afficherMot(1,1,"Hello World!", NOIR);

}
