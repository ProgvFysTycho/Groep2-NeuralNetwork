#Marjan Demuynck #Tycho Cools #Robbe Ceulemans #Yannick van den Steen

# Shell
SHELL = /bin/bash
# Compiler
COMPILER = g++ -g -std=c++11 -Wall -Wno-deprecated -O3 -DNDEBUG


.PHONY: all clean


all: TestNetwork Network.o Layer.o Neuron.o


TestNetwork: testNetworkMain.cpp Network.o Layer.o Neuron.o
	$(COMPILER) testNetworkMain.cpp Network.o Layer.o Neuron.o -o $@

Network.o: Network.cpp Network.h
	$(COMPILER) -c Network.cpp -o $@

Layer.o: Layer.cpp Layer.h
	$(COMPILER) -c Layer.cpp -o $@

Neuron.o: Neuron.cpp Neuron.h
	$(COMPILER) -c Neuron.cpp -o $@

clean : 
	rm *.o TestNetwork

