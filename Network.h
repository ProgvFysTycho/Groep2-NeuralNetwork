#include"Neuron.h"
#include"NeuronLayer.h"

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

class network{
	public:
		network(vector<vector<vector<float>>> NetworkWeights, vector<vector<float>> NetworkBias); //Constructor1, when weights and biases are loaded from a file.
		network(vector<int> nNeurons, int nInputs); //Constructor2, when no weights or biases are given. Paramters are # neurons for every layer, #inputs for the first layer of neurons, # layers.
		~network(); //Destructor
		network(const network &net); //Copy constructor
		
		//Assigment operator

		void setWeights(vector<vector<vector<float>>>);
		void setBias(vector<vector<float>>);
		//void setNumberofLayers(int);

		vector<vector<vector<float>>> getWeights();
		vector<vector<float>> getBias();
		int getNumberofLayers();

		void loadLayers(string);
		void saveLayers(string);

		vector<vector<float>> errorFunc(vector<float>);
		vector<float> resultFunc(vector<float>);
		float costFunc(vector<float>,vector<float>);

	protected:
		vector<layer> Layers;
		int NumberofLayers;

		//bool NetworkHasChanged  
