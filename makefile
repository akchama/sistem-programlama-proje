# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = libs/Libfdr
INCLUDE = -I$(CLASSDIR)/include
CFLAGS = $(INCLUDE)
LIBS = $(CLASSDIR)/lib/libfdr.a

CC = gcc
EXECUTABLES = \
    bin/kripto \

all: $(EXECUTABLES)

clean:
	rm -f bin/*

bin/kripto: src/kripto.c 
	$(CC) -g $(CFLAGS) -o bin/kripto src/kripto.c $(LIBS)

