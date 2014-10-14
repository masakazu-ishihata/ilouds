# Makefile
TAR = test
CC = gcc -O6 -Wall
L = -lm -libary
OBJS = main.o ilouds.o
SHAD = -fPIC -shared
LIB = libilouds.so

all : $(TAR) lib
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(LIB) $(TAR) *~ *.bak

.c.o:	  $(CC) -c $<om

lib:
	$(CC) $(SHAD) -o $(LIB) ilouds.c $(L)

main.o: main.h ilouds.o
ilouds.o: ilouds.h
