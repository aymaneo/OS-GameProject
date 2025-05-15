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
#include <Applications/BrickManager.h>
#include <Applications/PlatformManager.h>
#include <Applications/Compteur.h>

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
Semaphore *ballSpawnSema; 
Clavier clavier;

PlatformManager& manager = PlatformManager::getInstance();
#define PAGINATION_USE 1
#define L_P1 's'
#define R_P1 'd'
#define L_P2 'j'
#define R_P2 'k'


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


void renderScene() {
    clear_offscreen_buffer(0);

    // Render walls
    for (size_t i = 0; i < 200; i++) {
        plot_square_offscreen(0, i, 1, 255);
        plot_square_offscreen(320 - 1, i, 1, 255);
    }

    // Render platforms
    draw_sprite_offscreen(PlatformManager::getInstance().sprite, 
							PLATFORM_WIDTH, PLATFORM_HEIGHT, 
							PlatformManager::getInstance().getPlatform1X(), 
							PlatformManager::getInstance().getPlatform1Y());
    draw_sprite_offscreen(PlatformManager::getInstance().sprite, 
							PLATFORM_WIDTH, PLATFORM_HEIGHT, 
							PlatformManager::getInstance().getPlatform2X(), 
							PlatformManager::getInstance().getPlatform2Y());

    // Render enemy platform
    draw_sprite_offscreen(PlatformManager::getInstance().sprite, 
							PLATFORM_WIDTH, PLATFORM_HEIGHT, 	
							PlatformManager::getInstance().getEnnemy_platformX(), 
							PlatformManager::getInstance().getEnnemy_platformY());
	
	// Render bricks
	 for (int i = 0; i < BrickManager::getInstance().getBrickCount(); ++i) {
        if (BrickManager::getInstance().getBrick(i)->status) {
            draw_sprite_offscreen(BrickManager::getInstance().sprite,
								BRICK_WIDTH, BRICK_HEIGHT,
								BrickManager::getInstance().bricks[i].x, BrickManager::getInstance().bricks[i].y);
        }
    }

    // Render balls
    Ball* ballBuffer[MAX_BALLS];
    int count = 0;
    BallManager::getInstance().getAllBalls(ballBuffer, MAX_BALLS, count);
    for (int i = 0; i < count; ++i) {
		// Beware of not auto deadlocking urself, 
		// a recurvise mutext would be more appropriate
		//BallManager::getInstance().mutex_liste[i].lock();
		if (BallManager::getInstance().getBall(i) != nullptr) {
			draw_sprite_offscreen(BallManager::getInstance().ball_sprite, 
							BALL_WIDTH, BALL_HEIGHT, 
							BallManager::getInstance().getX(i), BallManager::getInstance().getY(i));
		}
		//BallManager::getInstance().mutex_liste[i].unlock();
    }

    // render points
	draw_sprite_offscreen(Compteur::getInstance().getSpriteDizaine(), 
							NUM_WIDTH, NUM_HEIGHT, 
							318-2*NUM_WIDTH, 70);
	draw_sprite_offscreen(Compteur::getInstance().getSpriteUnite(), 
							NUM_WIDTH, NUM_HEIGHT, 
							318-NUM_WIDTH, 70);

    copy_offscreen_to_vga();
}

void inputBinderPlatform(void* arg) {
    while (true) {
		if (clavier.testChar())  {
			char c = clavier.getchar();
			if (c == L_P1) {
 
				PlatformManager::getInstance().movePlatform1Left();
				 
			}else if(c == R_P1) {
 
				PlatformManager::getInstance().movePlatform1Right();
				 
			}else if(c == L_P2) {
 
				PlatformManager::getInstance().movePlatform2Left();
			}else if (c == R_P2) {
				PlatformManager::getInstance().movePlatform2Right();
			}
		}
    }
}


void update_screen(void* arg) {
    while (true) {
		renderScene();
		thread_active_sleep(20);
    }
}


void moveBall(void* arg){
	while (true){
		Ball* ballBuffer[MAX_BALLS];
		int count = 0;
		BallManager::getInstance().getAllBalls(ballBuffer, MAX_BALLS, count);
		for (int i = 0; i < count; ++i) {
			if (BallManager::getInstance().getBall(i) != nullptr) {
 
				BallManager::getInstance().getBall(i)->move();
				 
				if (BallManager::getInstance().getBall(i)->getY() > 195) {
					BallManager::getInstance().removeBall(i); 
					ballSpawnSema->V();
				}
			}		
		}
		thread_active_sleep(10);
	}
}

void spawnBalls(void* arg){
	create_kernel_thread((kernel_thread_start_routine_t) moveBall, 
							(void*) nullptr);
	while (true){
		ballSpawnSema->P();
		BallManager::getInstance().addBall(
					PlatformManager::getInstance().getPlatform1X() + PLATFORM_WIDTH/2,
					PlatformManager::getInstance().getPlatform1Y() - BALL_HEIGHT,
					1 , -1);
		thread_active_sleep(5000);
	}
}


void update_ennemy_plat(void* arg) {
    while (true) {
		PlatformManager::getInstance().moveEnnemy_platformRight();
		thread_active_sleep(50);
	}
}


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Sextant_Init();
	
	BallManager::getInstance();
	BrickManager::getInstance();
	PlatformManager::getInstance();
	Compteur::getInstance();
	ballSpawnSema = new Semaphore(1);
	
	create_kernel_thread((kernel_thread_start_routine_t) update_screen, (void*) &monEcran);
	create_kernel_thread((kernel_thread_start_routine_t) update_ennemy_plat, (void*) nullptr);
	create_kernel_thread((kernel_thread_start_routine_t) inputBinderPlatform, (void*) &clavier);
	create_kernel_thread((kernel_thread_start_routine_t) spawnBalls, (void*) nullptr);
		
	thread_exit();
}
