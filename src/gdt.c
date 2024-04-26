#include "gdt.h"

#define SEGMENT_BASE 0
#define SEGMENT_LIMIT 0xFFFFF

#define CODE_RX_TYPE 0xA
#define DATA_RW_TYPE 0x2

#define GDT_NUM_ENTRIES 3

#define TSS_SEGSEL (5 * 8)

#pragma pack(1)
struct gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
};

#pragma pack(1)
struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
};

struct gdt_entry gdt_entries[GDT_NUM_ENTRIES];

void gdt_load_and_set(struct gdt_ptr *gdt_entry);
static void gdt_create_entry(uint32_t n, uint8_t pl, uint8_t type);

void gdt_init(void) {
  struct gdt_ptr gdt_ptr;
  gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_NUM_ENTRIES;
  gdt_ptr.base = (uint32_t)gdt_entries;

  gdt_create_entry(0, 0, 0);
  gdt_create_entry(1, PL0, CODE_RX_TYPE);
  gdt_create_entry(2, PL0, DATA_RW_TYPE);

  gdt_load_and_set(&gdt_ptr);
}

static void gdt_create_entry(uint32_t n, uint8_t pl, uint8_t type) {
  gdt_entries[n].base_low = (SEGMENT_BASE & 0xFFFF);
  gdt_entries[n].base_mid = (SEGMENT_BASE >> 16) & 0xFF;
  gdt_entries[n].base_high = (SEGMENT_BASE >> 24) & 0xFF;

  gdt_entries[n].limit_low = (SEGMENT_LIMIT & 0xFFFF);
  gdt_entries[n].granularity |= (0x01 << 7) | (0x01 << 6) | 0x0F;
  gdt_entries[n].access =
      (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
}
