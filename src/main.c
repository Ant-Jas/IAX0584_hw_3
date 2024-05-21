/*
File:         main.c
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.20
Description:  Main code file for homework assignment III - Local weather
              forecast.
*/

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <curl/curl.h>
#include <arg_parse.h>
#include <time_helper.h>
#include <data_downloader.h>
#include <main.h>

int main(int argc, char **argv)
{
    // Supported command line arguments
    struct argument_description options[] =
    {
        {ADD_LOC, "--rm_location", 2},
        {RM_LOC, "--add_location", 2},
        {DISP_FORECAST, "--forecast", 1}
    };
    
    // Default argument values
    struct argument arguments =
    {
        .display_forecast = false
    };
    
    // Check if to download new data
    if ((double)time(NULL) - get_saved_time() > SECONDS_IN_HOUR)
    {
        download_and_check_for_errors();
    }
    
    // Parse arguments if needed
    if (argc > MIN_ARGS_TO_PARSE)
    {
        parse_arguments(options, &arguments, argc, argv);
    }
    
    return EXIT_SUCCESS;
}


void download_and_check_for_errors(void)
{
    CURL *handle = curl_setup();
    if (!handle)
    {
        exit(EXIT_FAILURE);
    }
    if (curl_download(handle, XML_URL_OBSERVATIONS, XML_DATA_FILE_OBSERVATIONS))
    {
        exit(EXIT_FAILURE);
    }
    if (curl_download(handle, XML_URL_FORECASTS, XML_DATA_FILE_FORECASTS))
    {
        exit(EXIT_FAILURE);
    }
    save_current_time();
    curl_cleanup(&handle);
}
