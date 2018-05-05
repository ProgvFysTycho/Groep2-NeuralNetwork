# makefile for the class 'network' 
# with a program 'TestNetwork_saveLayers' for testing the 'saveLayers' function
 
# Shell
SHELL = /bin/bash
# Compiler
COMPILER = g++ -g -std=c++11 -Wall -Wno-deprecated -O3 -DNDEBUG


.SUFFIXES:
.SUFFIXES: .cpp .o
.PHONY: all clean


all: TestNetwork_saveLayers network.o


# Target definitions

TestNetwork_saveLayers: TestNetwork_saveLayers.cpp network.o
	$(COMPILER) TestNetwork_saveLayers.cpp network.o -o $@

network.o: network.cpp network.h
	$(COMPILER) -c network.cpp -o $@


# clean up
clean:
	rm TestNetwork_saveLayers *.o
