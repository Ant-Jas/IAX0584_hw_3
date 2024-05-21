/*
File:         data_downloader.h
Author:       Anton Jaska
Created:      2024.00.00
Modified:     2024.05.20
Description:  Header file for data_downloader code file. Macros, function
              prototypes etc.
*/

#ifndef _DATA_DOWNLOADER_H
#define _DATA_DOWNLOADER_H

// https://www.ilmateenistus.ee/ilma_andmed/xml/observations.php
// https://www.ilmateenistus.ee/ilma_andmed/xml/forecast.php

// Download links
#define XML_URL_OBSERVATIONS "https://www.ilmateenistus.ee/ilma_andmed/xml/observations.php"
#define XML_URL_FORECASTS "https://www.ilmateenistus.ee/ilma_andmed/xml/forecast.php"

// Predefined output file names
#define XML_DATA_FILE_OBSERVATIONS "data/observations.xml"
#define XML_DATA_FILE_FORECASTS "data/forecast.xml"

#define CURL_DOWNLOAD_OK 0
#define CURL_DOWNLOAD_ERROR -1


/*
Description:    Initializes curl and sets necessary options for downloading data
                files. Preforms checks to verify that setup steps are
                successful. If a step is not successful preforms necessary
                cleanup.
                Based on libcurl sample: https://curl.se/libcurl/c/url2file.html

Parameter:      -

Return:         If no error occurred - A curl handle, that is ready to be used
                for downloading files.
                A NULL pointer if an error occurred.
*/
CURL *curl_setup(void);


/*
Description:    Sets file specific options before downloading, such as URL and
                destination file name. Downloads the file and stores it on disk.
                Preforms checks to verify if steps as successful. If a step is
                not successful preforms necessary cleanup.
                Based on libcurl sample: https://curl.se/libcurl/c/url2file.html

Parameter:      *curl_handle - A previously set up curl handle by function
                curl_setup.
                *url - String with the download URL.
                *f_name - Name of the output file.

Return:         If successful - CURL_DOWNLOAD_OK.
                Else - CURL_DOWNLOAD_ERROR.
*/
int curl_download(CURL *curl_handle, char *url, const char *f_name);


/*
Description:    Calls function curl_easy_cleanup to cleanup stuff related to
                passed curl handle. Makes the handle a NULL pointer for safety.
                Calls function curl_global_cleanup to releases resources
                acquired by curl_global_init.

Parameter:      **curl_handle - Handle acquired by curl_easy_init, that needs
                cleanup.

Return:         -
*/
void curl_cleanup(CURL **curl_handle);


/*
Description:    Prints an error message about a failed attempt to change an
                option for a curl handle. Message includes the error code.
                Function curl_cleanup is called.

Parameter:      err - Error code obtained from curl_easy_setopt.
                **curl_handle - Handle for which an error occurred.

Return:         -
*/
void curl_option_fail_handler(int err, CURL **curl_handle);

#endif
