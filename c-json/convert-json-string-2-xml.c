#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main() {
    char *json_str = "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}";

    // Parse the JSON data
    struct json_object *json_obj = json_tokener_parse(json_str);

    // Create an XML document
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_node);

    // Convert the JSON data to XML nodes and add them to the XML document
    json_object_object_foreach(json_obj, key, val) {
        xmlNodePtr node = xmlNewChild(root_node, NULL, BAD_CAST key, BAD_CAST json_object_get_string(val));
    }

    // Write the XML document to a file
    xmlSaveFormatFileEnc("output.xml", doc, "UTF-8", 1);

    // Free the memory
    json_object_put(json_obj);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}

