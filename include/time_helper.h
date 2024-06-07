/*
File:         time_helper.h
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.30
Description:  Header file for time_helper code file. Macros, function prototypes
              etc.
*/

#ifndef _TIME_HELPER_H
#define _TIME_HELPER_H

#define TIME_STAMP_FILE "last_time_stamp.txt"

#define ERR_GETTING_TIME -1

#define TIME_BUF_LEN 32


/*
Description:    Opens file TIME_STAMP_FILE and returns the time stamp contained
                in it. If the program is unable to open the file or the file
                does not contain a correctly formatted time stamp, a negative
                value is returned and an error message is displayed.

Parameter:      -

Return:         UNIX time contained in TIME_STAMP_FILE.
                In case of error, a negative value.
*/
time_t get_saved_time(void);


/*
Description:    Tries to overwrite TIME_STAMP_FILE with the current local UNIX
                time stamp. The time stamp is saved as string with format
                "YYYY-MM-DD HH:MM:SS". Displays an error message, if unable to
                open TIME_STAMP_FILE.

Parameter:      -

Return:         -
*/
void save_current_time(void);

#endif
