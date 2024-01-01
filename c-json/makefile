COMPILE = gcc
IDIR    = -I/usr/include/libxml2
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -ljson-c -lxml2 -ljansson


all : test_json convert_json_to_xml_file convert_xml_to_json


test_json: test_json.c
	$(COMPILE) $(XFLAGS) -o test_json test_json.c  $(LIBS)


convert_json_to_xml_file: convert_json_to_xml_file.c
	$(COMPILE) $(XFLAGS) -o convert_json_to_xml_file convert_json_to_xml_file.c  $(IDIR) $(LIBS)


convert_xml_to_json: convert_xml_to_json.c
	$(COMPILE) $(XFLAGS) -o convert_xml_to_json convert_xml_to_json.c $(IDIR) $(LIBS)

clean:
	rm test_json convert_json_to_xml_file convert_xml_to_json
