# Breakout on Sextant

This project implements a multiplayer Vintage Breakout game running directly Sextant. It was developed as part of our Operating Systems UE at IMT Atlantique.

## Features

- Two-player platform controls using keyboard input
- Auto-moving enemy platform
- Ball management (spawn, movement, collisions)
- Brick wall that resets when cleared
- Score display
- Buffered VGA rendering (mode 13h)

## Controls

- Player 1: `s` (left), `d` (right)
- Player 2: `j` (left), `k` (right)

Balls spawn periodically up to a limit of 2 simultaneously and destroy bricks on contact. The score increases as bricks are removed.

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
make clean && make && make run_gui
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

## Authors

Developed by Julien Million, Gregoire Le Bras et Aymane Ouraq
IMT Atlantique – UE Systèmes d'exploitation  
