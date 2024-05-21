/*
File:         time_helper.c
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.21
Description:  Functions for saving and getting a time stamp from a file.
*/

#include <stdio.h>
#include <time.h>
#include <time_helper.h>

double get_saved_time(void)
{
    FILE *fp = fopen(TIME_STAMP_FILE, "r");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file \"%s\" containing saved time.\n",
                        TIME_STAMP_FILE);
        return ERR_GETTING_TIME;
    }
    
    double time;  // for portability
    if (fscanf(fp, "%lf", &time) != 1)
    {
        fprintf(stderr, "File \"%s\" does not contain a time value.\n",
                        TIME_STAMP_FILE);
        fclose(fp);
        return ERR_GETTING_TIME;
    }
    
    fclose(fp);
    return time;
}

void save_current_time(void)
{
    FILE *fp = fopen(TIME_STAMP_FILE, "w");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file \"%s\" for saving current time.\n",
                        TIME_STAMP_FILE);
        return;
    }
    
    fprintf(fp, "%lf\n", difftime(time(NULL), (time_t)0)); // for portability
    fclose(fp);
}
