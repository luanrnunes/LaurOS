#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "string/string.h"

uint16_t* video_mem = 0;

uint16_t terminal_row = 0;
uint64_t terminal_col = 0;

uint16_t terminal_make_char (char c, char colour)
{
    return (colour << 8) | c; 
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH + x)] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if(c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print (const char* str)
{
    size_t len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void kernel_main()
{
    /*char*  video_mem = (char*)(0xB8000);
    
    video_mem[0] = 'A';
    video_mem[1] = 2;*/

    terminal_initialize();
    print("Kernel Initializing!\nComponents Loading...");

    // Initialize heap
    kheap_init();

    // Disk initialization
    disk_search_and_init();
    
    // Initialize the IDT
    idt_init();

    //4GB paging enable
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    //Swich to the kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    char* ptr = kzalloc(4096);
    paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x1000, (uint32_t)ptr | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);

    // Enable paging
    enable_paging();

    //Sys interrupts
    enable_interrupts();

    struct path_root* root_path = pathparser_parse("0:/bin/shell.exe", NULL);

    if (root_path)
    {

    }
}