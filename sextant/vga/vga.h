#ifndef VGA_H
#define VGA_H
extern volatile unsigned char *video;

void set_vga_mode13(void);
void clear_vga_screen(char color);
void plot_square(int x, int y, int size, unsigned char color);
void plot_palette(int x, int y, int size);
void set_palette_vga(unsigned char palette_vga[256][3]);
void draw_sprite(const unsigned char* sprite, int w, int h, int dstX, int dstY);
void clear_offscreen_buffer(char color);
void plot_square_offscreen(int x, int y, int size, unsigned char color);
void draw_sprite_offscreen(const unsigned char* sprite, int w, int h, int dstX, int dstY);
void copy_offscreen_to_vga();
#endif