/*
File:         dynamic_strings.h
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Header file for dynamic_strings.c. Macros, function prototypes,
              etc.
*/

#ifndef _DYNAMIC_STRINGS_H
#define _DYNAMIC_STRINGS_H

#define DYN_INPUT_STR_LEN_MIN 32


/*
Description:    Creates a dynamically allocated string, with the exact length
                needed for containing an origin string *orgn_str. If allocation
                is successful, copies the origin string over to the new string.
                
Parameters:     *orgn_str - Pointer to the origin string.
                
Return:         Pointer to the new dynamic string, if allocation was successful.
                NULL if allocation failed.
*/
char *dynamic_string(char *orgn_str);


/*
Description:    Reads provided input stream char-by-char until a newline symbol
                '\n' is encountered. Read chars are stored into a dynamically
                allocated string. The string is lengthened after every multiple
                of DYN_INPUT_STR_LEN_MIN chars read. Input stream must be
                flushed beforehand! If EOF flag is raised for the stream being
                read or memory allocation fails the string is freed. Excess
                allocated memory is freed, so returned string uses the exact
                amount of memory needed. Function also logs/prints appropriate
                messages/errors.
                INPUT STREAM MUST BE FLUSHED BEFOREHAND!
                
Parameters:     stream - Pointer to input stream being read.
                
Return:         On success a pointer to a dynamically allocated string.
                On failure a NULL pointer.
*/
char *get_dynamic_input_string(FILE *stream);

#endif
