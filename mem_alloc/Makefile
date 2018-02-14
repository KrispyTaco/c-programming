#Make environment
INCLUDES=-I.
CC=gcc
CFLAGS=-I. -c -g -Wall $(INCLUDES)
LINKARGS=-lm
LIBS=-lm

#Files
OBJECT_FILES= proj2.o \
			  proj2support.o
#Productions
all: proj2

proj2 : $(OBJECT_FILES)
	$(CC) $(LINKARGS) $(OBJECT_FILES) -o $@ $(LIBS)

proj2.o : main.c proj2header.h
	$(CC) $(CFLAGS) $< -o $@

proj2support.o : proj2support.c proj2header.h
	$(CC) $(CFLAGS) $< -o $@

