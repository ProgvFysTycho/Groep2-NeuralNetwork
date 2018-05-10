// This program is used for testing the 'network' class

#include<iostream>
using std::cout;

#include <ctime>

#include <cstdlib>

#include <string>
using std::string;
using std::to_string;

#include <vector>
using std::vector;


#include "Network.h" // Header of class "network"



float RandomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int main()
{
    cout << "Beginning of program 'TestNetwork'." << '\n';

    srand (static_cast <unsigned> (time(0))); // initialize the random generator rand() with a seed
    const float randMin = -1.0;
    const float randMax = 1.0;

    //========================================================================================
    //// Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    // Ninputs: number of inputs for network, Nlayers: number of layers in the network
    const int Ninputs = 8;
    const int Nlayers = 2;
    const int layer[Nlayers+1] = {Ninputs, 4, 3}; // layer[#] contains the amount of neurons in each layer # 
  							// except the first layer, it is the input layer which doesn't contain neurons
      
     vector<int> nNeurons (layer+1, layer + sizeof(layer) / sizeof(int)); 
      
      						
    // Bias //
    vector<vector<float> > testBias;	// The vector containing the values of the bias of the network
    for (int i=1; i < Nlayers+1; ++i)
    {
    	vector<float> biasOfLayer;	// A temporaly vector for a the bias of a layer
    	for (int j=0; j < layer[i] ; ++j)
    	{
    		biasOfLayer.push_back(RandomFloat(randMin,randMax));	// The values of the bias of neuron j(+1) in layer i are stored in the temporaly vector
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
    	    	weightsOfNeuron.push_back(RandomFloat(randMin,randMax));	// The values of the weight of neuron j(+1) in layer i with an input k(+1) from layer i-1
    	    }						// are stored.
    	    weightsOfLayer.push_back(weightsOfNeuron);	// The weights of neuron j(+1) are added to the weights of layer i
    	}
    	testWeights.push_back(weightsOfLayer);	// The weights of layer i are added to the weights of the network
    }
    //// End of Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    
    cout << "A network is contructed with " << Nlayers << " layers of neurons." << '\n';
    cout << "The number of neurons in the layers are: " << '\n';
    copy(nNeurons.begin(),nNeurons.end()-1,ostream_iterator<int>(cout,","));
    cout << nNeurons.back() << '\n';
    cout << "The network must process " << Ninputs << " inputs." << '\n';
    //==========================================================================================
    
    //// Begin of testing ////
    
    string fileName1("testFile.csv");
    
    network testNetwork(nNeurons,Ninputs);
    //network testNetwork(testWeights,testBias);
    testNetwork.saveLayers(fileName1); // To check if the constructors behave correctly.
    
    string fileName2("testFile2.csv");
    network anotherNetwork(testNetwork);
    //network anotherNetwork = testNetwork;
    anotherNetwork.saveLayers(fileName2);
    
    
    
    
    
    

    cout << "End of program 'TestNetwork'." << '\n';
    return 0;
}


