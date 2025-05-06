#ifndef SPRITE_H
#define SPRITE_H

<<<<<<<< HEAD:sextant/vga/sprite.h
#define SPRITE_WIDTH  100
#define SPRITE_HEIGHT 20

========
// Généré par png_to_c_with_palette.py à partir de 'pixel-32x32.png'
#define SPRITE_WIDTH  64
#define SPRITE_HEIGHT 16
>>>>>>>> bb7a93e (v1):Applications/brick_sprite.h

extern unsigned char palette_vga[256][3];
extern unsigned char sprite_data[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_door_data[SPRITE_WIDTH*SPRITE_HEIGHT];

#endif