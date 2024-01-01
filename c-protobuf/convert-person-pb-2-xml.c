#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <protobuf-c/protobuf-c.h>
#include "person.pb-c.h"

int main() {
  Person person = PERSON__INIT;
  person.name = "Alice";
  person.age = 30;
  person.email = "alice@example.com";

  size_t size = person__get_packed_size(&person);
  uint8_t *buffer = malloc(size);

  person__pack(&person, buffer);


  // Convert the binary protobuf message to an XML string
  ProtobufCMessage *message = person__unpack(NULL, size, buffer);
  char *xml_string = protobuf_c_message_to_string(message, &protobuf_c_xml_writer);

  // Write the XML string to a file
  FILE *xml_file = fopen("output.xml", "w");
  fprintf(xml_file, "%s", xml_string);
  fclose(xml_file);

  // Clean up
  free(buffer);
  free(xml_string);
  protobuf_c_message_free_unpacked(message, NULL);

  return 0;
}
