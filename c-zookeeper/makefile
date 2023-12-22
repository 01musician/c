#
#
#
#
#
COMPILE = gcc
IDIR    = -I/usr/include/libxml2
XFLAGS  = -ggdb -DNDEBUG
LIBS    = -ljson-c -lxml2 -ljansson


all : test-zookeeper


test-zookeeper: test-zookeeper.c
	$(COMPILE) $(XFLAGS) -o test-zookeeper test-zookeeper.c  $(LIBS)

clean:
	rm test-zookeeper

