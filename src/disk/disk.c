#include "io/io.h"
#include "disk.h"
#include "memory/memory.h"
#include "config.h"
#include  "status.h"

struct disk disk;
int disk_read_sector(int lba, int total, void* buffer)
{
    outb(0x1F6, (lba >> 24) | 0xE0);
    outb(0x1F2, total);
    outb(0x1F3, (unsigned char)(lba & 0xff));
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    unsigned short* ptr = (unsigned short*) buffer;

    for(int b = 0; b < total; b++)
    {
        // wait for the buffer to be ready
        char c = insb(0x1F7);
        while(!(c & 0x08))
        {
            c = insb(0x1F7);
        }

        // copy from HDD to RAM
        for(int i = 0; i < 256; i++)
        {
            *ptr = insw(0x1F0);
            ptr++;
        }
    }
    return 0;
}

void disk_search_and_init()
{
    memset(&disk, 0, sizeof(disk));
    disk.type = LAUROS_DISK_TYPE_REAL;
    disk.sector_size = LAUROS_SECTOR_SIZE;
}

struct disk* disk_get(int i)
{
    if(i != 0)
    {
        return 0;
    }
    return &disk;
}

int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buffer)
{
    if(idisk != &disk)
    {
        return -EIO;
    }
    return disk_read_sector(lba, total, buffer);
}