#
#
#
#
#
COMPILE = gcc
IDIR    = -I/usr/include/libxml2
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -ljson-c -lxml2 -ljansson


all : test_json convert_json_to_xml_file


test_json: test_json.c
	$(COMPILE) $(XFLAGS) -o test_json test_json.c  $(LIBS)


convert_json_to_xml_file: convert_json_to_xml_file.c
	$(COMPILE) $(XFLAGS) -o convert_json_to_xml_file convert_json_to_xml_file.c  $(IDIR) $(LIBS)

clean:
	rm test_json convert_json_to_xml_file

