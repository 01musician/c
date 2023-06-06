#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

int main() {
    // Read the XML file
    FILE* xmlFile = fopen("input.xml", "r");
    if (xmlFile == NULL) {
        printf("Failed to open the XML file.\n");
        return 1;
    }

    // Determine the size of the XML file
    fseek(xmlFile, 0, SEEK_END);
    long fileSize = ftell(xmlFile);
    rewind(xmlFile);

    // Allocate a buffer to hold the XML data
    char* xmlData = (char*)malloc(fileSize + 1);
    if (xmlData == NULL) {
        printf("Failed to allocate memory for XML data.\n");
        fclose(xmlFile);
        return 1;
    }

    // Read the XML data into the buffer
    fread(xmlData, 1, fileSize, xmlFile);
    xmlData[fileSize] = '\0'; // Null-terminate the data

    // Parse the XML data into a JSON object
    struct json_object* jsonObj = json_tokener_parse(xmlData);
    if (jsonObj == NULL) {
        printf("Failed to parse XML data.\n");
        free(xmlData);
        fclose(xmlFile);
        return 1;
    }

    // Generate the JSON string
    const char* jsonString = json_object_to_json_string_ext(jsonObj, JSON_C_TO_STRING_PRETTY);

    // Write the JSON string to a file
    FILE* jsonFile = fopen("output.json", "w");
    if (jsonFile == NULL) {
        printf("Failed to create the JSON file.\n");
        json_object_put(jsonObj);
        free(xmlData);
        fclose(xmlFile);
        return 1;
    }

    fprintf(jsonFile, "%s", jsonString);

    // Cleanup
    fclose(jsonFile);
    json_object_put(jsonObj);
    free(xmlData);
    fclose(xmlFile);

    printf("Conversion completed successfully.\n");

    return 0;
}

