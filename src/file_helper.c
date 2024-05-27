/*
File:         file_helper.c
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Functions to make file handling easier.
*/

#include <stdio.h>
#include <stdint.h>
#include <file_helper.h>


int file_over(FILE *fp)
{
    int64_t size = ftell(fp);
    while (fgetc(fp) == '\n');
    
    if (feof(fp))
    {
        return FILE_OVER;
    }
    else
    {
        fseek(fp, size, SEEK_SET);
    }
    
    return FILE_NOT_OVER;
}


FILE *open_file(char *f_name, char *mode)
{
    FILE *fp;
    fp = fopen(f_name, mode);
    if (!fp)
    {
        fprintf(stderr, "Unable to open file \"%s\" in mode "
                        "\"%s\".", f_name, mode);
        return NULL;
    }
    
    return fp;
}
