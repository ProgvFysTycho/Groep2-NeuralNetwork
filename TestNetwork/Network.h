#ifndef NETWORK_H
#define NETWORK_H

//#include"Neuron.h"
#include "Layer.h" // We only need the header "Layer.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm> //for copying vector content to savefile
// There should be a "boost" header file for the function 'loadLayers'

using namespace std;

class network {
	public:
		network(vector<vector<vector<float>>> NetworkWeights, vector<vector<float>> NetworkBias); //Constructor1, when weights and biases are loaded from a file.
		network(vector<int> nNeurons, int nInputs); //Constructor2, when no weights or biases are given. Paramters are # neurons for every layer, #inputs for the first layer of neurons, # layers.
		~network(); //Destructor
		network(const network &net); //Copy constructor
		
		//Assigment operator

		void setWeights(vector<vector<vector<float>>>);
		void setBias(vector<vector<float>>);
		void setNumberofLayers(int);

		vector<vector<vector<float>>> getWeights();
		vector<vector<float>> getBias();
		int getNumberofLayers();

		void loadLayers(const string);
		void saveLayers(const string);		// This function saves the current values of all the biases and weights in the network
			

		vector<vector<float>> errorFunc(vector<float>);
		vector<float> resultFunc(vector<float>);
		float costFunc(vector<float>,vector<float>);

	protected:
		vector<layer> Layers;
		int NumberofLayers;

		//bool NetworkHasChanged  
};
#endif // NETWORK_H
