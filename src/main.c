/*
File:         main.c
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.21
Description:  Main code file for homework assignment III - Local weather
              forecast.
*/

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <curl/curl.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <arg_parse.h>
#include <time_helper.h>
#include <data_downloader.h>
#include <xml_helper.h>
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
    
    // Parse XML documents and get root nodes
    struct xml_doc_pointers xml_ptrs =
    {
        .observations_doc = NULL,
        .forecasts_doc = NULL,
        .observations_root = NULL,
        .forecasts_root = NULL
    };
    prepare_xml_documents(&xml_ptrs);
    
    // Parse arguments if needed
    if (argc > MIN_ARGS_TO_PARSE)
    {
        parse_arguments(options, &arguments, argc, argv);
    }
    
    // Free resources acquired by XML documents
    free_xml_resources(&xml_ptrs.observations_doc, &xml_ptrs.forecasts_doc);
    
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


void prepare_xml_documents(struct xml_doc_pointers *ptrs)
{
    xmlDoc *obs_doc = NULL;
    xmlDoc *frcst_doc = NULL;
    
    obs_doc = parse_xml_doc(XML_DATA_FILE_OBSERVATIONS);
    if (!obs_doc)
    {
        fprintf(stderr, "Error parsing \"%s\".\n", XML_DATA_FILE_OBSERVATIONS);
        free_xml_resources(&obs_doc, &frcst_doc);
        exit(EXIT_FAILURE);
    }
    
    frcst_doc = parse_xml_doc(XML_DATA_FILE_FORECASTS);
    if (!frcst_doc)
    {
        fprintf(stderr, "Error parsing \"%s\".\n", XML_DATA_FILE_OBSERVATIONS);
        free_xml_resources(&obs_doc, &frcst_doc);
        exit(EXIT_FAILURE);
    }
    
    xmlNode *obs_root = NULL;
    xmlNode *frcst_root = NULL;
    
    obs_root = get_xml_root_element(XML_OBSERVATIONS_ROOT_NODE, &obs_doc);
    if (!obs_root)
    {
        fprintf(stderr, "Error getting root node \"%s\".\n",
                        XML_OBSERVATIONS_ROOT_NODE);
        free_xml_resources(&obs_doc, &frcst_doc);
        exit(EXIT_FAILURE);
    }
    
    frcst_root = get_xml_root_element(XML_FORECASTS_ROOT_NODE, &frcst_doc);
    if (!frcst_root)
    {
        fprintf(stderr, "Error getting root node \"%s\".\n",
                        XML_FORECASTS_ROOT_NODE);
        free_xml_resources(&obs_doc, &frcst_doc);
        exit(EXIT_FAILURE);
    }
    
    ptrs->observations_doc = obs_doc;
    ptrs->forecasts_doc = frcst_doc;
    ptrs->observations_root = obs_root;
    ptrs->forecasts_root = frcst_root;
}
