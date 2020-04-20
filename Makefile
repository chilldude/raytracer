# Makefile for raytracer

PROG = gradient
CC = g++

# debugging on
CPPFLAGS = -g -Wall
OBJS = gradient.o sphere.o main.o

gradient: clean
	$(CC) $(CPPFLAGS) -o gradient.o gradient.cpp

sphere: clean
	$(CC) $(CPPFLAGS) -o sphere.o sphere.cpp

main: clean
	$(CC) $(CPPFLAGS) -o main.o main.cpp

clean:
	rm -f OBJS
