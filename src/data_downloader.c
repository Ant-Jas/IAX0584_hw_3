/*
File:         data_downloader.c
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.21
Description:  A modified curl example (https://curl.se/libcurl/c/url2file.html)
              for downloading weather data.
*/

#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <data_downloader.h>


CURL *curl_setup(void)
{
    CURL *curl_handle;
    
    if (curl_global_init(CURL_GLOBAL_ALL))
    {
        fprintf(stderr, "Something went wrong while initializing curl.\n");
        return NULL;
    }
    
    // init the curl session
    curl_handle = curl_easy_init();
    if (!curl_handle)
    {
        fprintf(stderr, "Something went wrong while initializing curl.\n");
        curl_global_cleanup();
        return NULL;
    }
    
    int return_val;
    
    // Switch on full protocol/debug output while testing
    return_val = curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
    if (return_val != CURLE_OK)
    {
        curl_option_fail_handler(return_val, &curl_handle);
        return NULL;
    }
    
    // Disable progress meter, set to 0L to enable it
    return_val = curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    if (return_val != CURLE_OK)
    {
        curl_option_fail_handler(return_val, &curl_handle);
        return NULL;
    }
    
    // Send all data to this function - using default
    return_val = curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, NULL);
    if (return_val != CURLE_OK)
    {
        curl_option_fail_handler(return_val, &curl_handle);
        return NULL;
    }
    
    return curl_handle;
}


int curl_download(CURL *curl_handle, char *url, const char *f_name)
{
    int return_val;
    
    // Set URL to get here
    return_val = curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    if (return_val != CURLE_OK)
    {
        curl_option_fail_handler(return_val, &curl_handle);
        return CURL_DOWNLOAD_ERROR;
    }
    
    // Open the file
    FILE *f_out = fopen(f_name, "wb");
    if (f_out)
    {
        // Write the page body to this file handle
        return_val = curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, f_out);
        if (return_val != CURLE_OK)
        {
            curl_option_fail_handler(return_val, &curl_handle);
            fclose(f_out);
            return CURL_DOWNLOAD_ERROR;
        }
        
        // Get it!
        curl_easy_perform(curl_handle);
        
        // Close the header file
        fclose(f_out);
    }
    else
    {
        fprintf(stderr, "Download process is unable to open \"%s\".\n", f_name);
        curl_cleanup(&curl_handle);
        return CURL_DOWNLOAD_ERROR;
    }
    
    return CURL_DOWNLOAD_OK;
}


void curl_cleanup(CURL **curl_handle)
{
    curl_easy_cleanup(*curl_handle);
    *curl_handle = NULL;
    curl_global_cleanup();
}


void curl_option_fail_handler(int err, CURL **curl_handle)
{
    fprintf(stderr, "Encountered error with code %d, while trying to set curl "
                    "options.\n", err);
    curl_cleanup(curl_handle);
}
