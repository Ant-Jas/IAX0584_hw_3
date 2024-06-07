/*
File:         verify_and_print.h
Author:       Anton Jaska
Created:      2024.05.27
Modified:     2024.06.07
Description:  Header file for verify_and_print.c. Macros, function prototypes
              etc.
*/

#ifndef _VERIFY_AND_PRINT_H
#define _VERIFY_AND_PRINT_H

// Forecasts document node, attribute names and printing constants
#define FOR_NODE_NAME_FORECAST  (xmlChar *)"forecast"
#define FOR_NODE_NAME_NIGHT     (xmlChar *)"night"
#define FOR_NODE_NAME_DAY       (xmlChar *)"day"
#define FOR_NODE_NAME_TEMP_MIN  (xmlChar *)"tempmin"
#define FOR_NODE_NAME_TEMP_MAX  (xmlChar *)"tempmax"

#define FOR_ATTRBT_NAME_DATE (xmlChar *)"date"

#define FOR_NODE_NAME_PRINT ((const char*[]){\
                                    "Date", \
                                    "Minimum night temperature", \
                                    "Maximum night temperature", \
                                    "Minimum day temperature", \
                                    "Maximum day temperature"\
                                    })

// Observation document node names and printing constants
#define OBS_NODE_NAME_STATION   (xmlChar *)"station"

#define OBS_NODE_NAME ((const xmlChar*[]){\
                                    (xmlChar *)"name", \
                                    (xmlChar *)"longitude", \
                                    (xmlChar *)"latitude", \
                                    (xmlChar *)"phenomenon", \
                                    (xmlChar *)"precipitations", \
                                    (xmlChar *)"airpressure", \
                                    (xmlChar *)"relativehumidity", \
                                    (xmlChar *)"airtemperature", \
                                    (xmlChar *)"windspeed", \
                                    (xmlChar *)"windspeedmax"\
                                    })

#define OBS_NODE_NAME_PRINT ((const char*[]){\
                                    "Station", \
                                    "Longitude", \
                                    "Latitude", \
                                    "Phenomenon", \
                                    "Precipitations", \
                                    "Air pressure", \
                                    "Relative humidity", \
                                    "Air temperature", \
                                    "Wind speed", \
                                    "Maximum wind speed"\
                                    })

/*
    Named indexes for FOR_NODE_NAME_PRINT and arrays length count.
*/
enum forecast_data {FR_DATE, FR_NIGHT_TEMP_MIN, FR_NIGHT_TEMP_MAX,
                    FR_DAY_TEMP_MIN, FR_DAY_TEMP_MAX, FR_DATA_PNTS_CNT};

/*
    Named indexes for OBS_NODE_NAME, OBS_NODE_NAME_PRINT and arrays length
    count.
*/
enum station_data {ST_NAME, ST_LON, ST_LAT, ST_PHENOM, ST_PRECIP, ST_AIRPRES,
                   ST_RELHUM, ST_TEMP, ST_WINDSPD, ST_WINDMAX,
                   ST_DATA_PNTS_CNT};


/*
Description:    Every location read from the favorites file and added as a
                command line argument is checked against all possible locations
                in the observations XML file. Invalid locations are removed.
                A function to display data from valid observation locations is
                called if argument display_observations is true.
                
Parameters:     xml_wrp - A wrapper that holds pointers to prepared XML
                documents and their root nodes.
                *fav_wrp - A wrapper that contains a pointer to the beginning of
                a pointer array and the the length of the array. The array is
                for strings containing location names.
                args - A wrapper containing values resulting from parsing
                command line arguments.
                
Return:         -
*/
void verify_and_print_observations(struct xml_doc_pointers xml_wrp,
                                   struct favorites_wrapper *fav_wrp,
                                   struct argument args);


/*
Description:    For all the available days in the forecast XML document, the
                date, minimum and maximum day and night temperatures are
                printed.
                
Parameters:     xml_wrp - A wrapper that holds pointers to prepared XML
                documents and their root nodes.
                
Return:         -
*/
void print_forecast(struct xml_doc_pointers xml_wrp);


xmlNode *find_node_by_name(xmlNode **p_node, const xmlChar *node_name);


/*
Description:    Finds all nodes and their values, that are necessary for
                printing a locations observation data. Prints the observation
                data. If node has no data "N/A" is printed as its value.
                Function does not search for station name. It is assumed that
                the name already exists, because the station was verified by
                name. A function is called to print an open street map URL with
                a pin to the station location.
                
Parameters:     *doc - Pointer to the observations XML document.
                *p_node - Pointer to station node, that will be printed. The
                node is the parent node of all this stations data nodes.
                *p_name - The name of the station.
                
Return:         -
*/
void print_station_node(xmlDoc *doc, xmlNode *p_node, xmlChar *p_name);


/*
Description:    Composes an open street map URL with a pin at the location of
                the station.
                
Parameters:     **p_data - Pointer to pointer array containing longitude and
                latitude of a given station.
                
Return:         -
*/
void print_open_street_map_url_and_free(xmlChar **p_data);

#endif
