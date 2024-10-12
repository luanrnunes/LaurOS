#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_desc
{
    uint16_t offset_1; // offset bits 0-15
    uint16_t selector; // Selector on our GDT
    uint8_t zero; // Does nothing, unused set to to zero
    uint8_t type_attr; // Descriptor type & attributes
    uint16_t offset_2; // Offset bits 16-31
} __attribute__((packed));

struct idtr_desc
{
    uint16_t limit; //size of descriptor table -1
    uint32_t base; // base address of the start of the interupt descriptor table
} __attribute__((packed));

#endif