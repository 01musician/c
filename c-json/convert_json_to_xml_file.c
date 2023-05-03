#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void add_json_node_to_xml(json_t *node, xmlNodePtr xml_parent);

int main(int argc, char **argv)
{
    //Load JSON data from a file
	FILE *fp = fopen("input.json", "r");
	if (!fp) {
		perror("Failed to open input file");
		exit(1);
	}

	json_error_t error;
	json_t *root = json_loadf(fp, 0, &error);
	if (!root) {
		fprintf(stderr, "Failed to parse JSON: %s\n", error.text);
		exit(1);
	}

	fclose(fp);

	//Create the root element of the XML tree
	xmlDocPtr xml_doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr xml_root = xmlNewNode(NULL, BAD_CAST "data");
	xmlDocSetRootElement(xml_doc, xml_root);

	//Convert JSON to XML recursively
	add_json_node_to_xml(root, xml_root);

	//Save the XML tree to a file
	xmlSaveFormatFileEnc("output.xml", xml_doc, "UTF-8", 1);

	//Clean up
	xmlFreeDoc(xml_doc);
	json_decref(root);

	return 0;
}

void add_json_node_to_xml(json_t *node, xmlNodePtr xml_parent)
{
	switch (json_typeof(node)) {
		case JSON_OBJECT: {
					  json_t *value;
					  const char *key;
					  xmlNodePtr xml_node;

					  json_object_foreach(node, key, value) {
						  xml_node = xmlNewChild(xml_parent, NULL, BAD_CAST key, NULL);
						  add_json_node_to_xml(value, xml_node);
					  }
					  break;
				  }
		case JSON_ARRAY: {
					 json_t *value;
					 size_t index;
					 xmlNodePtr xml_node;

					 json_array_foreach(node, index, value) {
						 xml_node = xmlNewChild(xml_parent, NULL, BAD_CAST "item", NULL);
						 add_json_node_to_xml(value, xml_node);
					 }
					 break;
				 }
		case JSON_STRING: {
					  xmlNodeSetContent(xml_parent, BAD_CAST json_string_value(node));
					  break;
				  }
		case JSON_INTEGER: {
					   char buf[20];
					   snprintf(buf, sizeof(buf), "%lld", json_integer_value(node));
					   xmlNodeSetContent(xml_parent, BAD_CAST buf);
					   break;
				   }
		case JSON_REAL: {
					char buf[40];
					snprintf(buf, sizeof(buf), "%g", json_real_value(node));
					xmlNodeSetContent(xml_parent, BAD_CAST buf);
					break;
				}
		case JSON_TRUE: {
					xmlNodeSetContent(xml_parent, BAD_CAST "true");
					break;
				}
		case JSON_FALSE: {
					 xmlNodeSetContent(xml_parent, BAD_CAST "false");
					 break;
				 }
		case JSON_NULL: {
					xmlNodeSetContent(xml_parent, BAD_CAST "");
					break;
				}
	}
}

