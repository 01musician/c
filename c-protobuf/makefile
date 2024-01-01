#
#
#
#
#
COMPILE = gcc
IDIR    = -I/usr/include/libxml2
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -lprotobuf-c -lxml2


all : test-person-pb


test-person-pb: test-person-pb.c
	$(COMPILE) $(XFLAGS) -o test-person-pb test-person-pb.c person.pb-c.c $(LIBS)


convert-json-string-2-xml: convert-json-string-2-xml.c
	$(COMPILE) $(XFLAGS) -o convert-json-string-2-xml convert-json-string-2-xml.c $(IDIR) $(LIBS)
clean:
	rm test-person-pb convert-json-string-2-xml


