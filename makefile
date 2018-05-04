SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall
#Macros
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs)

CPPFLAGS = $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)


all:propagate

propagate: test.cpp
	$(COMPILER) test.cpp -o test


clean : 
	rm test
