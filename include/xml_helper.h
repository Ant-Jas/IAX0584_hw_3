/*
File:         xml_helper.h
Author:       Anton Jaska
Created:      2024.05.20
Modified:     2024.05.20
Description:  Header file for xml_helper.c. Macros, function prototypes etc.
              Based on libxml2 sample: https://gitlab.gnome.org/GNOME/libxml2/-/wikis/Tutorial
*/

#ifndef _XML_HELPER_H
#define _XML_HELPER_H

#define XML_OBSERVATIONS_ROOT_NODE (const xmlChar*)"observations"
#define XML_FORECASTS_ROOT_NODE (const xmlChar*)"forecasts"


/*
Description:    Parses an XML document and checks if parsing was successful. If
                not, an error message is displayed.
                
Parameters:     *doc_name - String containing the path and name of an XML
                document, that is going to be parsed.
                
Return:         Pointer to parsed document document.
                NULL if an error occurred.
*/
xmlDoc *parse_xml_doc(char *doc_name);


/*
Description:    Gets a pointer to the root node of the XML file. Verifies that
                the document is not empty and root node has a correct name. If
                verification fails, an appropriate error is displayed and the
                document is safely freed.
                
Parameters:     *root_name - String containing the name of the root node.
                **doc - Double pointer to parsed XML document, that is being
                searched.
                
Return:         Pointer to root node of document.
                NULL if root element does not exist.
*/
xmlNode *get_xml_root_element(const xmlChar *root_name, xmlDoc **doc);


void free_xml_resources(xmlDoc **obsrv, xmlDoc **frcst);

#endif
