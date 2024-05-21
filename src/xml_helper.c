/*
File:         xml_helper.c
Author:       Anton Jaska
Created:      2024.05.21
Modified:     2024.05.21
Description:  Functions for working with xml data files.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


xmlDoc *parse_xml_doc(char *doc_name)
{
    xmlDoc *doc;
    
    doc = xmlParseFile(doc_name);
    if (doc == NULL )
    {
        fprintf(stderr, "Failed to parse document.\n");
        return NULL;
    }
    
    return doc;
}


xmlNode *get_xml_root_element(const xmlChar *root_name, xmlDoc **doc)
{
    xmlNode *p_node;
    
    p_node = xmlDocGetRootElement(*doc);
    if (!p_node)
    {
        fprintf(stderr, "Document is empty.\n");
        xmlFreeDoc(*doc);
        *doc = NULL;  // xmlFreeDoc does not set freed pointer as NULL
        return NULL;
    }
    
    if (xmlStrcmp(p_node->name, root_name))
    {
        fprintf(stderr,"Root node \"%s\" does not exist.\n", root_name);
        xmlFreeDoc(*doc);
        *doc = NULL;  // xmlFreeDoc does not set freed pointer as NULL
        return NULL;
    }
    
    return p_node;
}


void free_xml_resources(xmlDoc **obsrv, xmlDoc **frcst)
{
    xmlFreeDoc(*obsrv);
    *obsrv = NULL;
    xmlFreeDoc(*frcst);
    *frcst = NULL;
}
/*
    
    p_node = p_node->xmlChildrenNode;
    while (p_node != NULL)
    {
        if ((!xmlStrcmp(p_node->name, (const xmlChar *)"station")))
        {
            parseStory (doc, p_node);
        }
         
        p_node = p_node->next;
    }
    
    xmlFreeDoc(doc);
    return;
}

void
parseStory (xmlDocPtr doc, xmlNodePtr cur) {

	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("Jaam: %s\n", key);
		    xmlFree(key);
 	    }
	cur = cur->next;
	}
    return;
}

*/
