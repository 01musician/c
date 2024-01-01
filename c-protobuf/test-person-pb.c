#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.pb-c.h"

int main() {
  Person person = PERSON__INIT;
  person.name = "Alice";
  person.age = 30;
  person.email = "alice@example.com";

  size_t size = person__get_packed_size(&person);
  uint8_t *buffer = malloc(size);

  person__pack(&person, buffer);

  // Print the serialized message
  for (int i = 0; i < size; i++) {
    printf("%02x ", buffer[i]);
  }
  printf("\n");

  free(buffer);

  return 0;
}

