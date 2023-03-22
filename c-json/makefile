#
#
#
#
#
COMPILE = gcc
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -ljson-c


all : test_json


test_json: test_json.c
	$(COMPILE) $(XFLAGS) -o test_json test_json.c  $(LIBS)

clean:
	rm test_json

