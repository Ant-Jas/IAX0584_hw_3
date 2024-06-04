/*
File:         verify_and_print.h
Author:       Anton Jaska
Created:      2024.05.27
Modified:     2024.05.27
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

enum forecast_data {FR_DATE, FR_NIGHT_TEMP_MIN, FR_NIGHT_TEMP_MAX,
                    FR_DAY_TEMP_MIN, FR_DAY_TEMP_MAX, FR_DATA_PNTS_CNT};


enum station_data {ST_NAME, ST_LON, ST_LAT, ST_PHENOM, ST_PRECIP, ST_AIRPRES,
                   ST_RELHUM, ST_TEMP, ST_WINDSPD, ST_WINDMAX,
                   ST_DATA_PNTS_CNT};


void verify_and_print_observations(struct xml_doc_pointers xml_wrp,
                                   struct favorites_wrapper *fav_wrp,
                                   struct argument args);


void print_forecast(struct xml_doc_pointers xml_wrp);


xmlNode *find_node_by_name(xmlNode **p_node, const xmlChar *node_name);


void print_station_node(xmlDoc *doc, xmlNode *p_node, xmlChar *p_name);


void print_open_street_map_url_and_free(xmlChar **p_data);

#endif
