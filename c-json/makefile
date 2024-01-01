#
#
#
#
#
COMPILE = gcc
IDIR    = -I/usr/include/libxml2
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -ljson-c -lxml2


all : test_json


test_json: test_json.c
	$(COMPILE) $(XFLAGS) -o test_json test_json.c  $(LIBS)


convert-json-string-2-xml: convert-json-string-2-xml.c
	$(COMPILE) $(XFLAGS) -o convert-json-string-2-xml convert-json-string-2-xml.c $(IDIR) $(LIBS)
clean:
	rm test_json convert-json-string-2-xml


