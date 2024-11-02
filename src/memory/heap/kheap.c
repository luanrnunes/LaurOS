#include "kheap.h"
#include "heap.h"
#include "config.h"
#include "kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init()
{
    int total_table_entries = LAUROS_HEAP_SIZE_BYTES / LAUROS_HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)(LAUROS_HEAP_TABLE_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(LAUROS_HEAP_ADDRESS + LAUROS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void*)(LAUROS_HEAP_ADDRESS), end, &kernel_heap_table);

    if (res < 0)
    {
        print("Fatal HEAP Error!\n");
    }
}