# Breakout on Sextant

This project implements a cooperative Breakout game running directly on a minimalist operating system kernel (Sextant), without relying on any external OS or runtime. It was developed as part of the Operating Systems coursework at IMT Atlantique.

## Features

- Two-player platform controls using keyboard input
- Auto-moving enemy platform
- Ball management (spawn, movement, collisions)
- Brick wall that resets when cleared
- Score display
- Double-buffered VGA rendering (mode 13h)

## Controls

- Player 1: `S` (left), `D` (right)
- Player 2: `J` (left), `K` (right)

Balls spawn periodically and destroy bricks on contact. The score increases as bricks are removed. The game continues as bricks regenerate when all are destroyed.

## Requirements

To build and run this project, you need:

- `make`
- `gcc` and `g++`
- `nasm`
- `qemu-system-x86_64`

Optional: VSCode with DevContainer support for development.

## How to Build and Run

From the project root:

```bash
make clean
make
make run_gui
```

### Manual QEMU Launch

If `make run_gui` is not available, you can launch it manually:

```bash
qemu-system-x86_64 -cdrom build/boot/grub.iso
```

## Project Structure

- `Applications/` — Game entities: ball, platform, brick, scoreboard
- `drivers/` — Low-level keyboard, timer, screen handling
- `sextant/` — Kernel subsystems: threading, memory, interrupts
- `hal/` — Boot and multiboot setup
- `Makefile` — Build instructions

## Notes

- All rendering is done using VGA mode 13h with offscreen buffering
- Input is handled via IRQ-based keyboard interrupt
- Timing and scheduling rely on periodic IRQ0 timer interrupts
- No dynamic memory allocation is used (only static and controlled `new`)

## Authors

Developed by [Your Names Here]  
IMT Atlantique – UE Systèmes d'exploitation  
May 2025
