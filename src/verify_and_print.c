/*
File:         verify_and_print.c
Author:       Anton Jaska
Created:      2024.05.27
Modified:     2024.06.07
Description:  Functions for verifying if locations added by user are correct.
              Also functions for printing observation and forecast info.
*/
#include <stdio.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <main.h>
#include <arg_parse.h>
#include <favorites_processing.h>
#include <verify_and_print.h>


void verify_and_print_observations(struct xml_doc_pointers xml_wrp,
                                   struct favorites_wrapper *fav_wrp,
                                   struct argument args)
{
    xmlNode *p_cur;
    xmlNode *p_station;
    xmlNode *p_name;
    xmlChar *p_str;
    xmlNode *p_temp;
    
    for (int i = 0; i < fav_wrp->len; i++)
    {
        // Skips removed entries
        while (i < fav_wrp->len && !(*(fav_wrp->data + i)))
        {
            i++;
        }
        // No more entries in favorites list
        if (i >= fav_wrp->len)
        {
            break;
        }
        
        p_cur = xml_wrp.observations_root->xmlChildrenNode;
        while (1)
        {
            p_station = find_node_by_name(&p_cur, OBS_NODE_NAME_STATION);
            // Station doesn't exist
            if (!p_station && !args.using_defaults)
            {
                fprintf(stderr, "Station \"%s\" does not exist.\n",
                                *(fav_wrp->data + i));
                remove_location(fav_wrp, *(fav_wrp->data + i), i);
                break;
            }
            // Name for default location changed
            else if (!p_station)
            {
                fprintf(stderr, "Default station with name \"%s\" no longer "
                                "exists.\n", *(fav_wrp->data + i));
                break;
            }
            
            p_temp = p_station->xmlChildrenNode;
            p_name = find_node_by_name(&p_temp, *(OBS_NODE_NAME + ST_NAME));
            // Station has no node <name>
            if (!p_name)
            {
                fprintf(stderr, "No child node with name \"%s\" exists for "
                                "parent node \"%s\".\n",
                                *(OBS_NODE_NAME + ST_NAME),
                                OBS_NODE_NAME_STATION);
                break;
            }
            
            p_str = xmlNodeListGetString(xml_wrp.observations_doc,
                                         p_name->xmlChildrenNode, 1);
            // Station name does not match
            if (xmlStrcmp(p_str, (xmlChar *)*(fav_wrp->data + i)))
            {
                xmlFree(p_str);
                p_cur = p_cur->next; // Advance pointer
                continue;
            }
            // Station name is verified, data will be printed
            else if (args.display_observations)
            {
                print_station_node(xml_wrp.observations_doc, p_station, p_str);
                xmlFree(p_str);
                break;
            }
            // Station name is verified, no data is printed
            else
            {
                xmlFree(p_str);
                break;
            }
        }
    }
}


void print_forecast(struct xml_doc_pointers xml_wrp)
{
    xmlNode *p_forecast;
    xmlNode *p_temp;
    xmlNode *p_night;
    xmlNode *p_day;
    xmlChar *p_str = NULL;
    
    xmlChar *p_data[FR_DATA_PNTS_CNT] = {NULL};
    
    p_forecast = xml_wrp.forecasts_root->xmlChildrenNode;
    
    while (1)
    {
        find_node_by_name(&p_forecast, FOR_NODE_NAME_FORECAST);
        if (!p_forecast)
        {
            break;
        }
        
        p_str = xmlGetProp(p_forecast, FOR_ATTRBT_NAME_DATE);
        *(p_data + FR_DATE) = p_str;
        
        // Get night data
        p_temp = p_forecast->xmlChildrenNode;
        p_night = find_node_by_name(&p_temp, FOR_NODE_NAME_NIGHT);
        if (!p_night)
        {
            fprintf(stderr, "No node with name \"%s\" found in XML file.\n",
                    FOR_NODE_NAME_NIGHT);
        }
        
        // Get night temperatures
        p_night = p_night->xmlChildrenNode;
        while (p_night)
        {
            if (!(*(p_data + FR_NIGHT_TEMP_MIN)) &&
                !xmlStrcmp(p_night->name, FOR_NODE_NAME_TEMP_MIN))
            {
                *(p_data + FR_NIGHT_TEMP_MIN) = xmlNodeListGetString(
                                                xml_wrp.forecasts_doc,
                                                p_night->xmlChildrenNode, 1);
            }
            else if (!(*(p_data + FR_NIGHT_TEMP_MAX)) &&
                     !xmlStrcmp(p_night->name, FOR_NODE_NAME_TEMP_MAX))
            {
                *(p_data + FR_NIGHT_TEMP_MAX) = xmlNodeListGetString(
                                                xml_wrp.forecasts_doc,
                                                p_night->xmlChildrenNode, 1);
            }
            else if (*(p_data + FR_NIGHT_TEMP_MIN) &&
                     *(p_data + FR_NIGHT_TEMP_MAX))
            {
                break;
            }
            
            p_night = p_night->next;
        }
        
        // Get day data
        p_temp = p_forecast->xmlChildrenNode;
        p_day = find_node_by_name(&p_temp, FOR_NODE_NAME_DAY);
        if (!p_day)
        {
            fprintf(stderr, "No node with name \"%s\" found in XML file.\n",
                    FOR_NODE_NAME_DAY);
        }
        
        // Get day temperatures
        p_day = p_day->xmlChildrenNode;
        while (p_day)
        {
            if (!(*(p_data + FR_DAY_TEMP_MIN)) &&
                !xmlStrcmp(p_day->name, FOR_NODE_NAME_TEMP_MIN))
            {
                *(p_data + FR_DAY_TEMP_MIN) = xmlNodeListGetString(
                                              xml_wrp.forecasts_doc,
                                              p_day->xmlChildrenNode, 1);
            }
            else if (!(*(p_data + FR_DAY_TEMP_MAX)) &&
                     !xmlStrcmp(p_day->name, FOR_NODE_NAME_TEMP_MAX))
            {
                *(p_data + FR_DAY_TEMP_MAX) = xmlNodeListGetString(
                                              xml_wrp.forecasts_doc,
                                              p_day->xmlChildrenNode, 1);
            }
            else if (*(p_data + FR_DAY_TEMP_MIN) &&
                     *(p_data + FR_DAY_TEMP_MAX))
            {
                break;
            }
            
            p_day = p_day->next;
        }
        
        // Print a days forecast
        printf("\n%s: %s\n", *(FOR_NODE_NAME_PRINT + FR_DATE),
                p_str ? p_str : (xmlChar *)"Date attribute not found");
        xmlFree(*(p_data + FR_DATE));
        *(p_data + FR_DATE) = NULL;
        
        for (int i = FR_NIGHT_TEMP_MIN; i < FR_DATA_PNTS_CNT; i++)
        {
            printf("\t%-28s: %s\n", *(FOR_NODE_NAME_PRINT + i),
                    *(p_data + i) ? *(p_data + i) : (xmlChar *)"N/A");
            xmlFree(*(p_data + i));
            *(p_data + i) = NULL;
        }
        
        p_forecast = p_forecast->next;
    }
}


xmlNode *find_node_by_name(xmlNode **p_node, const xmlChar *node_name)
{
    while (*p_node)
    {
        if (!xmlStrcmp((*p_node)->name, node_name))
        {
            return *p_node;
        }
        
        *p_node = (*p_node)->next;
    }
    
    return NULL;
}


void print_station_node(xmlDoc *doc, xmlNode *p_node, xmlChar *p_name)
{
    xmlChar *p_data[ST_DATA_PNTS_CNT] = {NULL};
    *(p_data + ST_NAME) = p_name;
    
    p_node = p_node->xmlChildrenNode;
    
    // Get data from document
    while (p_node)
    {
        // Skipping ST_NAME, because we already have it
        for (int i = ST_LON; i < ST_DATA_PNTS_CNT; i++)
        {
            // First condition checks if node already exists or not (NULL ptr)
            // Second condition checks current node's name with a list of node
            // names we are interested in
            if (!(*(p_data + i)) &&
                !xmlStrcmp(p_node->name, *(OBS_NODE_NAME + i)))
            {
                *(p_data + i) = xmlNodeListGetString(doc,
                                                     p_node->xmlChildrenNode,
                                                     1);
                break;
            }
        }
        
        p_node = p_node->next;
    }
    
    // Print data
    putchar('\n');
    printf("%s: %s\n", *(OBS_NODE_NAME_PRINT + ST_NAME),                       
           *(p_data + ST_NAME) ? *(p_data + ST_NAME) : (xmlChar *)"N/A");
    
    for (int i = ST_PHENOM; i < ST_DATA_PNTS_CNT; i++)
    {
        printf("\t%-20s: %s\n", *(OBS_NODE_NAME_PRINT + i),
               *(p_data + i) ? *(p_data + i) : (xmlChar *)"N/A");
        xmlFree(*(p_data + i));
        *(p_data + i) = NULL;
    }
    
    print_open_street_map_url_and_free(p_data);
}


void print_open_street_map_url_and_free(xmlChar **p_data)
{
    printf("https://www.openstreetmap.org/?mlat=%s"
           "&mlon=%s"
           "#map=8/58.600/25.600\n",
           *(p_data + ST_LAT), *(p_data + ST_LON));
    
    xmlFree(*(p_data + ST_LON));
    xmlFree(*(p_data + ST_LAT));
    *(p_data + ST_LON) = NULL;
    *(p_data + ST_LAT) = NULL;
}
