#include "framebuffer.h"
#include "gdt.h"

void main() {
  gdt_init();
  write("Hello world");
}