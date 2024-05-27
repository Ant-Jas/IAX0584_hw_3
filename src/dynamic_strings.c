/*
File:         dynamic_strings.c
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Code for working with dynamic strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dynamic_strings.h>


char *dynamic_string(char *orgn_str)
{
    char *dest_str = malloc(sizeof(char) * (strlen(orgn_str) + 1));
    if (dest_str == NULL)
    {
        return NULL;
    }
    strcpy(dest_str, orgn_str);
    
    return dest_str;
}


char *get_dynamic_input_string(FILE *stream)
{
    char *str = NULL;
    char *temp = NULL;
    int chars_read = 0;
    int cur_str_len = 0;
    
    // INPUT STREAM MUST BE FLUSHED BEFOREHAND !!!
    while (1)
    {
        // Allocate more memory, if string is full
        if (cur_str_len <= chars_read)
        {
            cur_str_len += DYN_INPUT_STR_LEN_MIN;
            temp = realloc(str, (size_t)cur_str_len);
            if (temp == NULL)
            {
                char *err = "Failed to allocate memory for dynamic string "
                            "while reading input.";
                fprintf(stderr, "%s\n", err);
                free(str);
                
                return NULL;
            }
            str = temp;
        }
        
        *(str + chars_read) = (char)fgetc(stream);
        if (feof(stream))
        {
            char *err = "Unexpected EOF occurred while reading input into "
                        "dynamic string.";
            fprintf(stderr, "%s\n", err);
            free(str);
            
            return NULL;
        }
        
        if (*(str + chars_read) == '\n')
        {
            *(str + chars_read) = '\0';
            break;
        }
        
        chars_read++;
    }
    
    // Free unused allocated memory
    temp = dynamic_string(str);
    if (temp == NULL)
    {
        char *err = "Failed to reallocate input string to shorten it.";
        fprintf(stderr, "%s\n", err);
    }
    free(str);
    str = temp;
    
    return str;
}
