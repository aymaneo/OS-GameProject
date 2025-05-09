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
#include <sextant/ordonnancements/preemptif/time.h>
#include <sextant/types.h>
#include <sextant/Synchronisation/Spinlock/Spinlock.h>
#include <sextant/memoire/segmentation/gdt.h>
#include <sextant/memoire/Memoire.h>
#include <sextant/memoire/MemoirePion.h>
#include <sextant/memoire/pagination/MemoirePhysique.h>
#include <sextant/memoire/pagination/Pagination.h>
#include <Applications/Platform.h>
#include <sextant/vga/vga.h>
#include <sextant/vga/sprite.h>
#include "Synchronisation/Mutex/Mutex.h"
#include <Applications/BallManager.h>

//#include <Applications/Entity/Entity.h>


extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom;	//Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;		//Taille de la pile d'exécution

Timer timer;
//paddr_t kernel_core_base,kernel_core_top;
unsigned long address;



Ecran ecran;
memoire *InterfaceMemoire;
Ecran *monEcran = &ecran;
Semaphore *ballSema; 
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
	set_vga_mode13(); 
	set_palette_vga(palette_vga);
}

#define L_P1 's'
#define R_P1 'd'
#define L_P2 'j'
#define R_P2 'k'
void update_plat(void* arg) {
    Clavier* keyboard = static_cast<Clavier*>(arg);
    while (true) {
		char c = keyboard->getchar();
		if (c == L_P1) {
            PlatformManager::getInstance().getPlatform1().moveLeft();
        }else if(c == R_P1) {
            PlatformManager::getInstance().getPlatform1().moveRight();
        }else if(c == L_P2) {
            PlatformManager::getInstance().getPlatform2().moveLeft();
        }else if (c == R_P2) {
            PlatformManager::getInstance().getPlatform2().moveRight();
        }
        thread_yield();
    }
}


void update_screen(void* arg) {
    Ecran* screen = static_cast<Ecran*>(arg);
	
    while (true) {
		screen->renderScene();
		thread_active_sleep(20);
    }
}


void moveBall(void* arg){
	Ball* ball = static_cast<Ball*>(arg);
	while (true){
		ball->move();
		thread_active_sleep(10);
	}
}

void spawnBalls(void* arg){
	//BallManager bmn = BallManager::getInstance();
	Platform plat = PlatformManager::getInstance().getPlatform1();
	while (true){	
		ballSema->P();
		BallManager::getInstance().addBall(
			PlatformManager::getInstance().getPlatform1().x, 
			PlatformManager::getInstance().getPlatform1().y - BALL_HEIGHT, 
			1 , -1);
			struct thread* balls_thread = create_kernel_thread(
				(kernel_thread_start_routine_t) moveBall, 
				(void*) BallManager::getInstance().getBall(BallManager::getInstance().getBallCount()-1));
		thread_active_sleep(5000);
	}
}


void update_ennemy_plat(void* arg) {
    Platform* ennemy_plat = static_cast<Platform*>(arg);
    while (true) {
		ennemy_plat->moveRight();
		thread_active_sleep(10);
	}
}


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Clavier clavier;
	Sextant_Init();
	
	PlatformManager& manager = PlatformManager::getInstance();
	BallManager& bm = BallManager::getInstance();

	ballSema = new Semaphore(5);
	
	struct thread* screen_thread = create_kernel_thread((kernel_thread_start_routine_t) update_screen, (void*) &monEcran);
	struct thread* ennemy_thread = create_kernel_thread((kernel_thread_start_routine_t) update_ennemy_plat, (void*) &(manager.getEnnemy_platform()));
	struct thread* event_thread = create_kernel_thread((kernel_thread_start_routine_t) update_plat, (void*) &clavier);
	struct thread* balls_thread = create_kernel_thread((kernel_thread_start_routine_t) spawnBalls, (void*) nullptr);
	



	
	thread_exit();
}
