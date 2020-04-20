# Makefile for raytracer

PROG = gradient
CC = g++

# debugging on
CPPFLAGS = -g -Wall
OBJS = gradient.o sphere.o

gradient: clean
	$(CC) $(CPPFLAGS) -o gradient.o gradient.cpp

sphere: clean
	$(CC) $(CPPFLAGS) -o sphere.o sphere.cpp

clean:
	rm -f OBJS
