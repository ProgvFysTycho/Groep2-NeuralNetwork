// This program is used for testing the 'network' class

#include<iostream>
using std::cout;
#include <ctime>
#include <cstdlib>
#include <string>
using std::string;
using std::to_string;
#include <iterator>
using std::ostream_iterator;
#include <vector>
using std::vector;
#include <algorithm>
using std::copy;

#include "Network.h" // Header of class "network"


int main()
{
    cout << "Beginning of program 'TestNetwork'." << '\n';

    //========================================================================================
    //// Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    // Ninputs: number of inputs for network, Nlayers: number of layers in the network
    const int Ninputs = 8;
    const int Nlayers = 2;
    const int layer[Nlayers+1] = {Ninputs,4,3}; // layer[#] contains the amount of neurons in each layer # 
  							// except the first layer, it is the input layer which doesn't contain neurons
      
     const vector<int> nNeurons (layer+1, layer + sizeof(layer) / sizeof(int)); 
      
      // Bias //
    vector<vector<float> > testBias;	// The vector containing the values of the bias of the network
    for (int i=1; i < Nlayers+1; ++i)
    {
    	vector<float> biasOfLayer;	// A temporaly vector for a the bias of a layer
    	for (int j=0; j < layer[i] ; ++j)
    	{
    		biasOfLayer.push_back(1.0);	// The values of the bias of neuron j(+1) in layer i are stored in the temporaly vector
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
    	    	weightsOfNeuron.push_back(1.0);	// The values of the weight of neuron j(+1) in layer i with an input k(+1) from layer i-1
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
    
    cout << "Start testing the network class" << "\n";

    string fileName1("testFile1.csv");
    string fileName2("testFile2.csv");
    
    network testNetwork(nNeurons,Ninputs); //Constructor 3, uses only the number of neurons in each layer and de number of inputs of the first layer
    testNetwork.saveLayers(fileName1); //
    //testNetwork.setWeights(testWeights); //
    //testNetwork.saveLayers(fileName2); //
    
    
    /*string fileName3("testFile3.csv");
    network testNetwork2(testWeights,testBias); //Constructor 1
    testNetwork2.saveLayers(fileName3);*/
    
    
    string fileName4("testFile4.csv");
    //testNetwork.loadLayers(fileName3);
    //network anotherNetwork(fileName3); // Constructor when weight and bias values are loaded from file, doesn't work yet.
    //network anotherNetwork(testNetwork); // Copy constructor
    //network anotherNetwork = testNetwork; // Assignment constructor
    testNetwork.saveLayers(fileName4);
    //anotherNetwork.getBias();    

    vector<float> a = {0.1, 0.8, 0.1};
    vector<float> y = {0, 1, 0};
     
    float C = testNetwork.costFunc(a,y); // OK
    
    /*
    //=============================================
    // test the resultFunc: use small # neurons and layers, and simple values for biases and weights 
    cout << "Begin of testing resultFunc." << '\n';
    testNetwork.setBias(testBias);
    testNetwork.setWeights(testWeights);
    
    // A way to create a vector of pointers to float (To group 1: why use pointer to float? )
    float x = 1;
    vector<float*> FInput(Ninputs); // vector that will contain the values of the inputs of the network 
	
	std::generate(FInput.begin(), FInput.end(),
		[&]() {
		return &x;
	});
	
    vector<float*> result = testNetwork.resultFunc(FInput);
    
    cout << "The vector 'result' contains: " << '\n';
    for (size_t i = 0 ; i < FInput.size() ; ++i)
    {
   	 cout << *FInput[i] << ",";
    }
    cout << '\n';*/


    cout << "End of program 'TestNetwork'." << '\n';
    return 0;
}


