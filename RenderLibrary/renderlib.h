#ifndef __RENDERLIB_H__
#define __RENDERLIB_H__

#include <windows.h>
#include <stdint.h>

typedef uint32_t COLOR;

int renderlib_create_window(WCHAR* title, int w, int h);
COLOR* renderlib_get_color_buffer();
void renderlib_update();
int renderlib_clear();
int renderlib_get_pixel(int x, int y, COLOR* color);
int renderlib_set_pixel(int x, int y, COLOR color);
void renderlib_draw_line(int x1, int y1, int x2, int y2, COLOR color);
int renderlib_write_bitmap(char *filename);
void renderlib_release();
void renderlib_sync_start();
void renderlib_sync_end(int hertz, int print_fps);

#endif // __RENDERLIB_H__
