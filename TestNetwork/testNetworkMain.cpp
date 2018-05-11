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


int main()
{
    cout << "Beginning of program 'TestNetwork'." << '\n';

    //========================================================================================
    //// Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    // Ninputs: number of inputs for network, Nlayers: number of layers in the network
    const int Ninputs = 8;
    const int Nlayers = 2;
    const int layer[Nlayers+1] = {Ninputs, 4, 3}; // layer[#] contains the amount of neurons in each layer # 
  							// except the first layer, it is the input layer which doesn't contain neurons
      
     vector<int> nNeurons (layer+1, layer + sizeof(layer) / sizeof(int)); 
      
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
    

    //vector<float*> result = testNetwork.resultFunc(Input);
    

    cout << "End of program 'TestNetwork'." << '\n';
    return 0;

    
}


