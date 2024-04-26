#include "framebuffer.h"
char *fb = (char *)0x000B8000;
unsigned int position = 0;

#define COLUMNS 80
#define ROWS 25
#define COLUMNS_LENGTH (COLUMNS * 2)
#define FRAMEBUFFER_SIZE (ROWS * COLUMNS_LENGTH)

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3d5

void outb(unsigned short port, unsigned char data);

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  fb[i] = c;
  fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

void write(const char *text) {
  for (text; *text; text++) {
    if (*text == '\n') {
      position = (position + COLUMNS_LENGTH) % FRAMEBUFFER_SIZE;
      position = (position / COLUMNS_LENGTH) * COLUMNS_LENGTH;
    } else {
      fb_write_cell(position, *text, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
      position = (position + 2) % FRAMEBUFFER_SIZE;
    }
    fb_move_cursor(position >> 1);
  }
}