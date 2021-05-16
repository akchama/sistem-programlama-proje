# If you want to use this on your own machine, change CLASSDIR and/or INCLUDE and LIBS so
# that they point to the correct directories/library.

CLASSDIR = libs/Libfdr
INCLUDE = -I$(CLASSDIR)/include
CFLAGS = $(INCLUDE)
LIBS = $(CLASSDIR)/lib/libfdr.a

CC = gcc
EXECUTABLES = kripto

all: $(EXECUTABLES)

clean:
	rm -f bin/*

kripto: main.c 
	$(CC) -g $(CFLAGS) -o kripto main.c $(LIBS)

