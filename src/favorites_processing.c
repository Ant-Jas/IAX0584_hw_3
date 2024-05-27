/*
File:         favorites_processing.c
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Functions that let the user add and remove favorite locations.
              Functions for saving, reading the favorites file and other useful
              functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_helper.h>
#include <dynamic_strings.h>
#include <favorites_processing.h>


int get_favorites(struct favorites_wrapper *wrp)
{
    FILE *fp = open_file(FAVORITES_FILE_NAME, "r");
    if(!fp)
    {
        return FAV_READ_ERR;
    }
    
    int count = 0;
    char **p_arr = NULL;
    char *name_buf;
    
    while (!file_over(fp))
    {
        name_buf = get_dynamic_input_string(fp);
        if (!name_buf)
        {
            fprintf(stderr, "Error reading line: %d\n", count + 1);
            wrp->data = p_arr;
            wrp->len = count;
            free_favorites(wrp);
            fclose(fp);
            
            return FAV_READ_ERR;
        }
        
        p_arr = expand_list(wrp);
        if (!p_arr)
        {
            fclose(fp);
            return FAV_READ_ERR;
        }
        
        *(p_arr + count) = name_buf;
        count++;
        
        wrp->data = p_arr;
        wrp->len = count;
    }
    
    fclose(fp);
    
    return FAV_READ_OK;
}


void free_favorites(struct favorites_wrapper *wrp)
{
    for (int i = 0; i < wrp->len; i++)
    {
        free(*(wrp->data + i));
    }
    free(wrp->data);
    wrp->data = NULL;
    wrp->len = 0;
}


int add_unique_location(struct favorites_wrapper *wrp, char *loc)
{
    int empty = -1;
    for (int i = 0; i < wrp->len; i++)
    {
        if (!(*(wrp->data + i)) && empty < 0)
        {
            empty = i;
        }
        else if (!strcmp(*(wrp->data + i), loc))
        {
            fprintf(stderr, "Location \"%s\" is already added as a favorite.\n",
                            loc);
            free(loc);
            loc = NULL;
            
            return FAV_EXISTS;
        }
    }
    
    if (empty >= 0)
    {
        *(wrp->data + empty) = loc;
        return empty;
    }
    else
    {
        char **p_arr = expand_list(wrp); 
        if(!p_arr)
        {
            return FAV_ADD_ERR;
        }
        else
        {
            wrp->data = p_arr;
            wrp->len++;
            *(wrp->data + wrp->len - 1) = loc;
            
            return wrp->len - 1;
        }
    }
}


void remove_location(struct favorites_wrapper *wrp, char *loc, int idx)
{
    for (int i = idx; i < wrp->len; i++)
    {
        if (*(wrp->data + i) && !strcmp(*(wrp->data + i), loc))
        {
            free(*(wrp->data + i));
            *(wrp->data + i) = NULL;
            
            return;
        }
    }
    
    fprintf(stderr, "Location \"%s\" is not set as a favorite.\n", loc);
}


char **expand_list(struct favorites_wrapper *wrp)
{
    char **p_temp = realloc(wrp->data, sizeof(char *) * (size_t)(wrp->len + 1));
    if (!p_temp)
    {
        fprintf(stderr, "Unable to expand data array from length %d to %d\n",
                wrp->len, wrp->len + 1);
        free_favorites(wrp);
    }
    
    return p_temp;
}


int save_favorites(struct favorites_wrapper wrp)
{
    FILE *fp = open_file(FAVORITES_FILE_NAME, "w");
    if(!fp)
    {
        return FAV_WRITE_ERR;
    }
    
    for (int i = 0; i < wrp.len; i++)
    {
        if (*(wrp.data + i))
        {
            fprintf(fp, "%s\n", *(wrp.data + i));
        }
    }
    fclose(fp);
    
    return FAV_WRITE_OK;
}
