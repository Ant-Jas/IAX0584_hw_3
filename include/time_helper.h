#ifndef _TIME_HELPER_H
#define _TIME_HELPER_H

#define TIME_STAMP_FILE "last_time_stamp.txt"

#define ERR_GETTING_TIME -1.0f


/*
Description:    Opens file TIME_STAMP_FILE and returns the time stamp contained
                in it. If the program is unable to open the file or the file
                does not contain a correctly formatted time stamp, a negative
                value is returned and an error message is displayed.

Parameter:      -

Return:         UNIX time contained in TIME_STAMP_FILE.
                In case of error, a negative value.
*/
double get_saved_time(void);


/*
Description:    Tries to overwrite TIME_STAMP_FILE with the current UNIX time
                stamp. The time stamp is saved as a double in an effort to
                improve portability (some precision might be lost). Displays an
                error message, if unable to TIME_STAMP_FILE.

Parameter:      -

Return:         -
*/
void save_current_time(void);

#endif