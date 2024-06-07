/*
File:         main.h
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.06.07
Description:  Header file for main code file. Data struct definitions, macros,
              function prototypes etc.
*/

#ifndef _MAIN_H
#define _MAIN_H

#define MIN_ARGS_TO_PARSE 1

#define SECONDS_IN_HOUR 3600

// Default locations if favorites are missing
#define DEFAULT_FAVORITES_CNT 3
#define DEFAULT_FAVORITE_LOCATIONS ((const char*[]){\
                                      "Tallinn-Harku", \
                                      "Tartu-Tõravere", \
                                      "Narva"\
                                      })

/*
    Holds pointers to prepared XML documents and their root nodes.
*/
struct xml_doc_pointers
{
    xmlDoc *observations_doc;
    xmlDoc *forecasts_doc;
    xmlNode *observations_root;
    xmlNode *forecasts_root;
};


/*
Description:    Calls all necessary function for downloading observations and
                forecasts data files. Checks return values and exits the program
                if an error occurs. If files are downloaded successfully calls
                appropriate functions to preform cleanup.
                
Parameters:     -
                
Return:         -
*/
void download_and_check_for_errors(void);


/*
Description:    Prepares XML data files for further use of the program.
                Necessary function for parsing the files and getting their root
                nodes are called. Pointers to prepared documents and root nodes
                are stored in a provided struct. If an error occurs while
                performing one of these operations, an error message is
                displayed. Also resources are freed safely and the program is
                closed.
                
Parameters:     *ptrs - A struct that will hold pointers to parsed documents and
                their root nodes, that the program will use. Pointers need to be
                initialized as NULL pointers.
                
Return:         -
*/
void prepare_xml_documents(struct xml_doc_pointers *ptrs);

#endif
