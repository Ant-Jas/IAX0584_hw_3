/*
File:         main.h
Author:       Anton Jaska
Created:      2024.00.00
Modified:     2024.05.20
Description:  Header file for main code file. Data struct definitions, macros,
              function prototypes etc.
*/

#ifndef _MAIN_H
#define _MAIN_H

#define MIN_ARGS_TO_PARSE 1

#define SECONDS_IN_HOUR 3600


/*
Description:    Calls all necessary function for downloading observations and
                forecasts data files. Checks return values and exits the program
                if an error occurs. If files are downloaded successfully calls
                appropriate functions to preform cleanup.
                
Parameters:     -
                
Return:         -
*/
void download_and_check_for_errors(void);

#endif
