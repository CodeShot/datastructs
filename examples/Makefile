CC=gcc
INCPATH=../
CFLAGS=-c -Wall -I$(INCPATH)
LDFLAGS=-ldatastructs
LIBPATH=../.libs/
CSOURCES=$(wildcard example_*.c)
COBJECTS=$(CSOURCES:.c=.o)
EXAMPLEAPPS=example_queue example_stack example_sequential example_binarytree\
			example_string example_binarytree2

all: $(COBJECTS) clean

$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $<
	$(CC) -L$(LIBPATH) $(LDFLAGS) -o $* $<

clean:
	rm -f $(COBJECTS)

allclean:
	rm -f $(EXAMPLEAPPS)
