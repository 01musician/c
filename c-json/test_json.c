#include <json-c/json.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    //create a new JSON object
    struct json_object *obj = json_object_new_object();

    //add some data to the object
    json_object_object_add(obj, "name", json_object_new_string("John"));
    json_object_object_add(obj, "age", json_object_new_int(42));
    json_object_object_add(obj, "isStudent", json_object_new_boolean(true));

    //print the JSON object to the console
    printf("JSON object: %s\n", json_object_to_json_string(obj));

    //get some data from the object
    struct json_object *name = NULL;
    struct json_object *age = NULL;
    struct json_object *isStudent = NULL;
    json_object_object_get_ex(obj, "name", &name);
    json_object_object_get_ex(obj, "age", &age);
    json_object_object_get_ex(obj, "isStudent", &isStudent);

    //print the data to the console
    printf("Name: %s\n", json_object_get_string(name));
    printf("Age: %d\n", json_object_get_int(age));
    printf("Is student: %s\n", json_object_get_boolean(isStudent) ? "true" : "false");

    //free the memory used by the JSON object
    json_object_put(obj);

    return 0;
}

