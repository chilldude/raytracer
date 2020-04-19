# Makefile for raytracer

PROG = gradient
CC = g++

# debugging on
CPPFLAGS = -g -Wall
OBJS = gradient.o

gradient: clean
	$(CC) $(CPPFLAGS) -o gradient gradient.cpp

clean:
	rm -f gradient
