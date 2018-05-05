#Robbe Ceulemans
#robbe.ceulemans@student.uantwerpen.be

#Makefile 

SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall



read: testcsvreader.cpp
	$(COMPILER) testcsvreader.cpp -o $@

