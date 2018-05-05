
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;

#include <algorithm>
using std::copy; // for copying vector content to savefile

// own class header file
#include "network.h"


// Constructor
network::network(int nlayers, int nNeurons[], vector<vector<vector<float> > >& inputWeights, vector<vector<float> >& inputBias)
:NumberOfLayers(2)
{
   cout << "Contructor of class 'network' is called." << endl; // For testing
   
   setNumberOfLayers(nlayers);
   setWeights(inputWeights);
   setBias(inputBias);
   
   
}

// Destructor
network::~network()
{
   cout << "Destructor of class 'network' is called." << endl; // For testing
}


void network::setWeights(const vector<vector<vector<float> > >& inputWeights)
{
    // exception handler needed
    TestWeights = inputWeights;
}

void network::setBias(const vector<vector<float> >& inputBias)
{
    // exception handler needed
    TestBias = inputBias;
}


void network::setNumberOfLayers(const int nlayers)
{
    // exception handler needed
    NumberOfLayers = nlayers;	
}

void network::setLayerNneurons(int nNeurons[])
{

}


int network::getNumberOfLayers() const
{
    return NumberOfLayers;
}





void network::saveLayers(const string filename) const
{

    // exception if the string 'filename' is invalid.
    cout << "Function 'saveLayers' is called." << endl; // For testing
    cout << "Filename is " << filename << "." << endl; // For testing
    
    ofstream saveFile(filename);
    // exception if file could not be opened.
    saveFile << "This is a test." << endl;
    
    
    
    saveFile.close();
    

}








