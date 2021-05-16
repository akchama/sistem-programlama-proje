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
	rm -f kripto

cleanall:
	rm -f kripto
	rm -f decrypted.txt
	rm -f encrypted
	rm -f istiklal_marsi.txt
	rm -f .kilit

kripto: main.c 
	$(CC) -g $(CFLAGS) -o kripto main.c $(LIBS)

run:
	make clean
	make
	./kripto -e istiklal_marsi.txt encrypted
	./kripto -d encrypted decrypted.txt