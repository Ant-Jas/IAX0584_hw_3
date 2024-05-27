/*
File:         file_helper.h
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Header file for file_helper.c. Macros, function prototypes,
              etc.
*/

#ifndef _FILE_HELPER_H
#define _FILE_HELPER_H

#define FILE_NOT_OVER 0
#define FILE_OVER 1


/*
Description:    Checks if a file is over by reading endlines '\n'. If EOF
                occurs after reading all consecutive endlines, then the file is
                considered to be over. If file is not over, the position
                indicator is set to the state before the function was called.
                
Parameters:     *fp - Pointer to file stream, that is being checked.
                
Return :        FILE_OVER - If file is over.
                FILE_NOT_OVER - If file is not over.
*/
int file_over(FILE *fp);


/*
Description:    A helper function for opening file with name f_name and in mode
                mode. Mode is a string similar to the ones passed to function
                fopen. Checks if file was opened successfully. Also handles
                error printing for associated actions.
                
Parameters:     *f_name - Pointer to string containing file name.
                *mode - Pointer to string containing info about how the file
                should be opened.
                
Return:         Pointer to opened file.
                NULL if unsuccessful.
*/
FILE *open_file(char *f_name, char *mode);

#endif
