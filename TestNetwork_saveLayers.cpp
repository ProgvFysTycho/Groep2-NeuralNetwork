// This program is used to test the 'saveLayers' function of class 'network'

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;
#include <iterator>
using std::ostream_iterator;

//#include "infix_iterator.h" same as 'ostream_iterator' wihout delimiter after last element


#include <algorithm>
using std::copy; // for copying vector content to savefile

#include "network.h"


int main()
{

    cout << "Beginning of program 'TestNetwork'." << endl;

    //// Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    // Ninputs: number of inputs for network, Nlayers: number of layers in the network
    const int Ninputs = 5;
    const int Nlayers = 3;
    const int layer[Nlayers+1] = {Ninputs, 4, 3, 3}; // layer[#] contains the amount of neurons in each layer # 
  							// except the first layer, it is the input layer which doesn't contain neurons
      							
    // Bias //
    vector<vector<float> > testBias;	// The vector containing the values of the bias of the network
    for (int i=1; i < Nlayers+1; ++i)
    {
    	vector<float> biasOfLayer;	// A temporaly vector for a the bias of a layer
    	for (int j=0; j < layer[i] ; ++j)
    	{
    		biasOfLayer.push_back(i+j+0.1);	// The values of the bias of neuron j(+1) in layer i are stored in the temporaly vector
    	}
    	testBias.push_back(biasOfLayer);	// The bias of layer i are added to the bias of the network
    }
 

    // Weights //
    vector<vector<vector<float> > > testWeights;	// The vector containing the values of the weights of the network.
    for (int i=1; i < Nlayers+1; ++i)
    {
    	vector<vector<float> > weightsOfLayer;	// A temporaly vector for the weights of a layer.
    	for (int j=0; j < layer[i] ; ++j)
    	{
    	    vector<float> weightsOfNeuron;	// A temporaly vector for the weights of a neuron.
    	    for (int k=0; k < layer[i-1] ; ++k)
    	    {
    	    	weightsOfNeuron.push_back(i+j+k+0.1);	// The values of the weight of neuron j(+1) in layer i with an input k(+1) from layer i-1
    	    }						// are stored.
    	    weightsOfLayer.push_back(weightsOfNeuron);	// The weights of neuron j(+1) are added to the weights of layer i
    	}
    	testWeights.push_back(weightsOfLayer);	// The weights of layer i are added to the weights of the network
    }
    //// End of Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    
    cout << "A network is contructed with " << Nlayers << " layers of neurons." << endl;
    cout << "The network must process " << Ninputs << " inputs." << endl;
    
    
     //// testsaveLayers function ////
     const string filename ("saveLayers.txt");
     // exception if the string 'filename' is invalid.
     cout << "Values of bias and weights of network will be printed to a file." << endl; // For testing
     cout << "Filename is " << filename << "." << endl; // For testing
    
     ofstream saveFile(filename);
     // exception if file could not be opened.
     
     // printing BIAS values to file
     saveFile << "BIAS; ";
    
    for (int i=1; i < Nlayers+1; ++i)
    {
    	saveFile << layer[i] << ", ";
    }
    saveFile << endl;
    
    vector<vector<float> >::const_iterator endBiasNetwork = testBias.end(); 
    for (vector<vector<float> >::const_iterator iter = testBias.begin() ; iter != endBiasNetwork ; ++iter)
    {
    	copy((*iter).begin(),(*iter).end(),ostream_iterator<float>(saveFile, ", "));
    	saveFile << ";\n";
    }
    saveFile << endl << endl;
    
    // printing WEIGHTS values to file
    saveFile << "WEIGHTS; ";
    for (int i=0; i < Nlayers+1; ++i)
    {
    	saveFile << layer[i] << ", ";
    }
     saveFile << endl;
    
    vector<vector<vector<float> > >::const_iterator endWeightsNetwork = testWeights.end();
    for (vector<vector<vector<float> > >::const_iterator iterLayer = testWeights.begin() ; iterLayer != endWeightsNetwork ; ++iterLayer)
    {
    	vector<vector<float> >::const_iterator endWeightsLayer = (*iterLayer).end();
    	for (vector<vector<float> >::const_iterator iterNeuron = (*iterLayer).begin() ; iterNeuron != endWeightsLayer ;  ++iterNeuron)
    	{
    		copy((*iterNeuron).begin(),(*iterNeuron).end(),ostream_iterator<float>(saveFile, ", "));
    		saveFile << ";\n";
    	}
    	saveFile << "\n";
    }   
    
    
    
    
    
    saveFile.close();
    


    
    
    /*
    // A test for the copy algorithm
    vector<float> testvec;
    for (int i=0; i<Nlayers; ++i)
    {
    	testvec.push_back(i);
    }
    
    ofstream testFile("testFilecopy.txt");
    testFile << "This is a test." << endl;
    copy(testvec.begin(),testvec.end(),ostream_iterator<float>(testFile, ", "));
    testFile << "\n";
    copy(testvec.begin(),testvec.end(),ostream_iterator<float>(testFile, ", "));
    testFile.close();
    */

  
    cout << "Program 'TestNetwork' has ended." << endl;
    
    return 0;
}

