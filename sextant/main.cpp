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
#include <sextant/memoire/MemoirePion.h>
#include <sextant/memoire/pagination/MemoirePhysique.h>
#include <sextant/memoire/pagination/Pagination.h>
#include <Applications/Platform.h>
#include <sextant/vga/vga.h>
#include <Applications/BalleManager.h>

extern char __e_kernel, __b_kernel, __b_data, __e_data, __b_stack, __e_load;
extern vaddr_t bootstrap_stack_bottom;
extern size_t bootstrap_stack_size;

Timer timer;
unsigned long address;

Ecran ecran;
memoire *InterfaceMemoire;
Ecran *monEcran = &ecran;

void Sextant_Init()
{
	idt_setup();
	irq_setup();
	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);
	asm volatile("sti\n");
	irq_set_routine(IRQ_KEYBOARD, handler_clavier);

	multiboot_info_t *mbi = (multiboot_info_t *)address;
	gdt_setup();
	InterfaceMemoire = memoire::nouveau();
	InterfaceMemoire->mem_setup(&__e_kernel, (mbi->mem_upper << 10) + (1 << 20), &ecran);
	thread_subsystem_setup(bootstrap_stack_bottom, bootstrap_stack_size);
	sched_subsystem_setup();
	irq_set_routine(IRQ_TIMER, sched_clk);

	set_vga_mode13();
	set_palette_vga(palette_vga);
}

#define L_P1 's'
#define R_P1 'd'
#define L_P2 'j'
#define R_P2 'k'

void update_plat(void *arg)
{
	Clavier *keyboard = static_cast<Clavier *>(arg);
	while (true)
	{
		char c = keyboard->getchar();
		if (c == L_P1)
			PlatformManager::getInstance().getPlatform1().moveLeft();
		else if (c == R_P1)
			PlatformManager::getInstance().getPlatform1().moveRight();
		else if (c == L_P2)
			PlatformManager::getInstance().getPlatform2().moveLeft();
		else if (c == R_P2)
			PlatformManager::getInstance().getPlatform2().moveRight();
		thread_yield();
	}
}

void update_screen(void *arg)
{
	Ecran *screen = static_cast<Ecran *>(arg);
	while (true)
	{
		screen->renderScene();
		thread_yield();
	}
}

void update_balle(void *arg)
{
	struct time t;
	t.sec = 0;
	t.nanosec = 50000000;
	while (true)
	{
		BalleManager::getInstance().update();
		thread_sleep(&t);
	}
}

extern "C" void Sextant_main(unsigned long magic, unsigned long addr)
{
	address = addr;
	Clavier clavier;
	Sextant_Init();

	PlatformManager &manager = PlatformManager::getInstance();
	ecran.effacerEcran(NOIR);

	Platform &p1 = manager.getPlatform1();
	BalleManager::getInstance().spawnBall(p1.x + 10, p1.y - Platform::size - 2);

	create_kernel_thread((kernel_thread_start_routine_t)update_plat, &clavier);
	create_kernel_thread((kernel_thread_start_routine_t)update_screen, monEcran);
	create_kernel_thread((kernel_thread_start_routine_t)update_balle, nullptr);

	thread_yield();
}
