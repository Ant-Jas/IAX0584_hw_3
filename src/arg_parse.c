/*
File:         arg_parse.c
Author:       Anton Jaska
Created:      2024.00.00
Modified:     2024.06.07
Description:  Code for parsing command line arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dynamic_strings.h>
#include <arg_parse.h>

int parse_arguments(struct argument_description *opts, struct argument *args,
                     int arg_cnt, char **arg_vec)
{
    int temp;
    for (int i = 1; i < arg_cnt; i++)
    {
        for (int j = 0; j < ARG_SUPPORTED_CNT; j++)
        {
            if (strcmp(*(arg_vec + i), (opts + j)->arg_name) == 0)
            {
                temp = change_argument_value(args, j, arg_vec, arg_cnt, i,
                                             (opts + j)->arg_mems);
                if (temp < 0)
                {
                    return temp;
                }
                
                i += temp;
                
                break;
            }
            if (j == (ARG_SUPPORTED_CNT - 1))
            {
                fprintf(stderr, "Unknown argument \"%s\" encountered.\n",
                        *(arg_vec + i));
            }
        }
    }
    
    return ARG_PARSE_OK;
}


int change_argument_value(struct argument *args, enum argument_cases event,
                          char **arg_vec, int arg_vec_len, int cnt, int arg_mems)
{
    if (arg_mems + cnt > arg_vec_len)
    {
        fprintf(stderr, "Not enough arguments provided. Check if every argument"
                        " has appropriate number of members.\n");
        return arg_mems - 1;
    }
    
    switch (event)
    {
        case ADD_LOC:
            char *location = dynamic_string(*(arg_vec + cnt + 1));
            if (!location)
            {
                return ARG_PARSE_ERR;
            }
            if (add_unique_location(&(args->locations), location) == FAV_ADD_ERR)
            {
                return ARG_PARSE_ERR;
            }
            args->display_observations = false;
            break;
            
        case RM_LOC:
            remove_location(&(args->locations), *(arg_vec + cnt + 1), 0);
            args->display_observations = false;
            break;
            
        case DISP_FORECAST:
            args->display_forecast = true;
            args->display_observations = false;
            break;
            
        default:
            fprintf(stderr, "Error with argument handling setup, check argument"
                            " case values. This is not a user error!\n");
            break;
    }
    
    return arg_mems - 1;
}
