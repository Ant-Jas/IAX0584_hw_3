/*
File:         time_helper.c
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.21
Description:  Functions for saving and getting a time stamp from a file.
*/

#include <stdio.h>
#include <stdlib.h>

#define __USE_XOPEN
#define _GNU_SOURCE

#include <time.h>
#include <dynamic_strings.h>
#include <time_helper.h>

time_t get_saved_time(void)
{
    FILE *fp = fopen(TIME_STAMP_FILE, "r");
    if (!fp)
    {
        fprintf(stderr, "Unable to open file \"%s\" containing saved time.\n",
                        TIME_STAMP_FILE);
        return ERR_GETTING_TIME;
    }
    
    char *buf = get_dynamic_input_string(fp);
    if (!buf)
    {
        return ERR_GETTING_TIME;
    }
    fclose (fp);
    
    struct tm time_st = {0};
    if(!strptime(buf, "%F %T", &time_st))
    {
        free(buf);
        return ERR_GETTING_TIME;
    }
    free(buf);
    
    time_t t = mktime(&time_st);
    if (t == -1)
    {
        fprintf(stderr, "Unable to represent string in \"%s\" as a time "
                        "value.\n", TIME_STAMP_FILE);
        return ERR_GETTING_TIME;
    }
    
    return t;
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
    
    time_t t = time(NULL);
    struct tm *p_time_st = localtime(&t);
    char buf[TIME_BUF_LEN];
    strftime(buf, TIME_BUF_LEN, "%F %T", p_time_st);
    fprintf(fp, "%s\n", buf);
    
    fclose(fp);
}
