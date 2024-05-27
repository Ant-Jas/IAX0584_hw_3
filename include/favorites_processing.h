/*
File:         favorites_processing.h
Author:       Anton Jaska
Created:      2024.05.23
Modified:     2024.05.23
Description:  Header file for favorites_processing.c. Data struct definitions,
              macros, etc.
*/

#ifndef _FAVORITES_PROCESSING_H
#define _FAVORITES_PROCESSING_H

#define FAVORITES_FILE_NAME "favorites.txt"

#define FAV_READ_ERR -1
#define FAV_READ_OK 0

#define FAV_WRITE_ERR -1
#define FAV_WRITE_OK 0

#define FAV_ADD_ERR -2
#define FAV_EXISTS -1

struct favorites_wrapper
{
    char **data;
    int len;
};


/*
Description:    Dynamically expands an array of pointers to strings. Each string
                contains a location name that the user has previously added as a
                favorite. The locations are read from FAVORITES_FILE_NAME.
                
Parameters:     *wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                
Return:         FAV_READ_OK if no errors occurred while getting favorites.
                FAV_READ_ERR if some error occurred.
*/
int get_favorites(struct favorites_wrapper *wrp);


/*
Description:    Frees all of the dynamically allocated strings in the array.
                Also frees the dynamically allocated array, sets it as a NULL
                pointer and sets the arrays length to be 0.
                
Parameters:     *wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                
Return:         -
*/
void free_favorites(struct favorites_wrapper *wrp);


/*
Description:    Adds a location to a dynamically allocated favorites array.
                Location is only added if it does not exist in the array
                already. If an empty spot exists in the array, the location is
                added to that spot. If no empty spot exists the array is
                dynamically expanded.
                
Parameters:     *wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                *loc - A pointer to a string that the user wishes to add as a
                new favorite.
                
Return:         The array index of the newly added location.
                FAV_EXISTS if the location is already added as a favorite.
                FAV_ADD_ERR if an error occurred while adding the location as a
                favorite.
*/
int add_unique_location(struct favorites_wrapper *wrp, char *loc);


/*
Description:    Removes a location from the favorites array. If the array index
                of the location being removed is known, set idx to the
                appropriate value. Otherwise set idx to 0, to search the whole
                array. The dynamically allocated string of the location is freed
                and its pointer in the array is set as a NULL pointer.
                
Parameters:     *wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                *loc - A pointer to a string that the user wishes to add as a
                new favorite.
                idx - If known, the array index of the element being removed.
                
Return:         -
*/
void remove_location(struct favorites_wrapper *wrp, char *loc, int idx);


/*
Description:    Expands the dynamic favorite locations array by one. Used by
                get_favorites and add_unique_location.
                
Parameters:     *wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                
Return:         Pointer to the expanded array.
                A NULL pointer if realloc failed.
*/
char **expand_list(struct favorites_wrapper *wrp);


/*
Description:    Saves all the locations in the favorite locations array to
                FAVORITES_FILE_NAME.
                
Parameters:     wrp - A wrapper that contains a pointer to the beginning of the
                pointer array and the the length of the array.
                
Return:         FAV_WRITE_OK - Locations saved successfully.
                FAV_WRITE_ERR - An error occurred while saving. Changes will be
                lost.
*/
int save_favorites(struct favorites_wrapper wrp);

#endif
