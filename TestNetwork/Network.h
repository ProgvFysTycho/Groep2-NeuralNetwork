#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h" 

#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm> //for copying vector content to savefile
#include <boost/algorithm/string.hpp>


using namespace std;

class network {
	public:
		network(const vector<vector<vector<float>>>& NetworkWeights, const vector<vector<float>>& NetworkBias); //Constructor1, when weights and biases vectors are given.
		network(const string fileName);					// Constructor2, when weights and bias values are loaded from a file
		network(const vector<int>& nNeurons, const int nInputs);	// Constructor3, when no weights or biases are given. Paramters are # neurons for every layer,
											// #inputs for the first layer of neurons, # layers.
		~network(); 							// Destructor
		network(const network& net); 					// Copy constructor
		network& operator = (const network& net); 			// Assignment constructor

		void setWeights(const vector<vector<vector<float>>>&);
		void setBias(const vector<vector<float>>&);
		void setNumberofLayers(const int);

		vector<vector<vector<float>>> getWeights();
		vector<vector<float>> getBias();
		int getNumberofLayers() const;

		void loadLayers(const string);
		void saveLayers(const string);		// This function saves the current values of all the biases and weights in the network
			

		//vector<vector<float>> errorFunc(vector<float>);
		//vector<float> resultFunc(vector<float>);
		//float costFunc(vector<float>,vector<float>);

	protected:
	
		// Data members
		vector<layer> Layers;
		int NumberofLayers;
		//bool NetworkHasChanged  
};
#endif // NETWORK_H
