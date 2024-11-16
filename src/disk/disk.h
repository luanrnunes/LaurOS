#ifndef DISK_H
#define DISK_H

#define LAUROS_DISK_TYPE_REAL 0

typedef unsigned int LAUROS_DISK_TYPE;

struct disk {
    LAUROS_DISK_TYPE type;
    int sector_size;
};

void disk_search_and_init();
struct disk* disk_get(int i);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buffer);

#endif