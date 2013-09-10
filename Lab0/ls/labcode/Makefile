
# Makefile, OS lab0
# Irene Huang, 2012/09/16

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g

OBJS1=lab0.o

all: lab0.out

lab0.out: $(OBJS1) 
	$(LD) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.out 
