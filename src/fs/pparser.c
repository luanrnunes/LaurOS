#include "pparser.h"
#include "kernel.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "status.h"

static int pathparser_path_valid_format(const char* filename)
{
    int len = strnlen(filename, LAUROS_MAX_PATH);
    return(len >= 3 && isdigit(filename[0]) && memcmp((void*)&filename[1], ":/", 2) == 0);
}

static int pathparser_get_drive_by_path(const char** path)
{
    if(!pathparser_path_valid_format(*path))
    {
        return -EBADPATH;
    }

    int drive_number = tonumericdigit(*path[0]);

    // 3 bytes to skip number
    *path += 3;;
    return drive_number;
}

static struct path_root* pathparser_create_root(int drive_number)
{
    struct path_root* path_r = kzalloc(sizeof(struct path_root));
    path_r->drive_no = drive_number;
    path_r->first = 0;
    return path_r;
}

static const char* pathparser_get_path_part(const char** path)
{
    char* result_path_part = kzalloc(LAUROS_MAX_PATH);
    int i = 0;

    while(**path != '/' && **path != 0x00)
    {
        result_path_part[i] == **path;
        *path += 1;
        i++
    }

    if (**path == '/')
    {
        *path + 1;
    }

    if(i == 0)
    {
        kfree(result_path_part);
        result_path_part = 0;
    }

}