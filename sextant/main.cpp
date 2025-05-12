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
Semaphore *ballUpdateMutex;
Semaphore *platformUpdateMutex;
Spinlock *ballUpdateSpinlock;
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
void intToConstChar(int number, char* buffer) {
    int i = 0;
    bool isNegative = false;

    if (number == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    while (number > 0) {
        buffer[i++] = (number % 10) + '0';
        number /= 10;
    }

    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    for (int j = 0, k = i - 1; j < k; ++j, --k) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }
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
	//platformUpdateMutex->P();
    draw_sprite_offscreen(PlatformManager::getInstance().sprite, 
							PLATFORM_WIDTH, PLATFORM_HEIGHT, 	
							PlatformManager::getInstance().getEnnemy_platformX(), 
							PlatformManager::getInstance().getEnnemy_platformY());
	//platformUpdateMutex->V();
	
	// Render bricks
	 for (int i = 0; i < BrickManager::getInstance().getBrickCount(); ++i) {
        if (BrickManager::getInstance().bricks[i].status) {
            draw_sprite_offscreen(BrickManager::getInstance().sprite,
                BRICK_WIDTH, BRICK_HEIGHT,
                BrickManager::getInstance().bricks[i].x, BrickManager::getInstance().bricks[i].y);
        }
    }

    // Render balls
    Ball* ballBuffer[MAX_BALLS];
    int count = 0;
    BallManager::getInstance().getAllBalls(ballBuffer, MAX_BALLS, count);
	//ballUpdateMutex->P();
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
	//ballUpdateMutex->V();

    copy_offscreen_to_vga();

	
	
}

void inputBinderPlatform(void* arg) {
    while (true) {
		if (clavier.testChar())  {
			char c = clavier.getchar();
			if (c == L_P1) {
				//platformUpdateMutex->P();
				PlatformManager::getInstance().movePlatform1Left();
				//platformUpdateMutex->V();
			}else if(c == R_P1) {
				//platformUpdateMutex->P();
				PlatformManager::getInstance().movePlatform1Right();
				//platformUpdateMutex->V();
			}else if(c == L_P2) {
				//platformUpdateMutex->P();
				PlatformManager::getInstance().movePlatform2Left();
				//platformUpdateMutex->V();
			}else if (c == R_P2) {
				//platformUpdateMutex->P();
				PlatformManager::getInstance().movePlatform2Right();
				//platformUpdateMutex->V();
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
		//ballUpdateMutex->P();
		for (int i = 0; i < count; ++i) {
			if (BallManager::getInstance().getBall(i) != nullptr) {
				//platformUpdateMutex->P();
				BallManager::getInstance().getBall(i)->move();
				//platformUpdateMutex->V();
				if (BallManager::getInstance().getBall(i)->getY() > 195) {
					BallManager::getInstance().removeBall(i); 
					ballSpawnSema->V();
				}
			}		
		}
		//ballUpdateMutex->V();
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
		thread_active_sleep(1000);
	}
}


void update_ennemy_plat(void* arg) {
    //Platform* ennemy_plat = static_cast<Platform*>(arg);
    while (true) {
		//platformUpdateMutex->P();
		PlatformManager::getInstance().moveEnnemy_platformRight();
		//platformUpdateMutex->V();
		thread_active_sleep(50);
		
	}
}


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Sextant_Init();
	
	BallManager::getInstance();
	BrickManager::getInstance();
	PlatformManager::getInstance();

	ballSpawnSema = new Semaphore(5);
	ballUpdateMutex = new Semaphore(1);
	platformUpdateMutex = new Semaphore(1);
	ballUpdateSpinlock = new Spinlock();
	
	create_kernel_thread((kernel_thread_start_routine_t) update_screen, (void*) &monEcran);
	create_kernel_thread((kernel_thread_start_routine_t) update_ennemy_plat, (void*) nullptr);
	create_kernel_thread((kernel_thread_start_routine_t) inputBinderPlatform, (void*) &clavier);
	create_kernel_thread((kernel_thread_start_routine_t) spawnBalls, (void*) nullptr);
		
	thread_exit();
}
