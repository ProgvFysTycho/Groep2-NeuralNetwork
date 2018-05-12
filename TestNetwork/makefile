#Marjan Demuynck #Tycho Cools #Robbe Ceulemans #Yannick van den Steen

# Shell
SHELL = /bin/bash
# Compiler
COMPILER = g++ -g -std=c++11 -Wall -Wno-deprecated -O3 -DNDEBUG


.PHONY: all clean


all: TestNetwork testNetworkMain.o Network.o Layer.o Neuron.o


TestNetwork: testNetworkMain.o Network.o Layer.o Neuron.o
	$(COMPILER) $^ -o $@
	
testNetworkMain.o: testNetworkMain.cpp Network.h
	$(COMPILER) -c testNetworkMain.cpp -o $@

Network.o: Network.cpp Network.h Layer.h
	$(COMPILER) -c Network.cpp -o $@

Layer.o: Layer.cpp Layer.h Neuron.h
	$(COMPILER) -c Layer.cpp -o $@

Neuron.o: Neuron.cpp Neuron.h
	$(COMPILER) -c Neuron.cpp -o $@

clean : 
	rm *.o TestNetwork

