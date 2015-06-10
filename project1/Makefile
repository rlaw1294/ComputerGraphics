##Author: Rachel Law
##Fall 2014 - CS 130

## CS130 Fall 2013: Computer Graphics
## Lab 1 Makefile
##
## This file does not need to be modified
#########################################

LIBS = -lglut -lGLU -lGL -lXmu -lXext -lXi -lX11 -lm
CC = g++

## Global header files
INCLUDE = point3d.h triangle.h transform.h

## Object files and executables
MAIN_OUT = a.out

## Requirements for each command
MAIN_REQS = main.cpp

## Targets to compile for each command
MAIN_TARGETS = main.cpp

all: main

## Main 
main: $(MAIN_REQS)
	$(CC) -w $(MAIN_TARGETS) $(LIBS) -o $(MAIN_OUT)

main2:$(MAIN_REQS)
	$(CC) -w main2.cpp $(LIBS) -o $(MAIN_OUT)

clean:
	rm -f *~ *.o *.out
