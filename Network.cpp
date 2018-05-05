#include"Neuron.h"
#include"NeuronLayer.h"
#include"Network.h"


using namespace std;

//Author: Robbe (& Marjan)=========================================================================
//Constructor for the network class when Weights and biases are loaded from a file
network::network(vector<vector<vector<float>>> NetworkWeights, vector<vector<float>> NetworkBias){
	
	//Possible argument check	

	NumberofLayers = NetworkWeights.size(); //The size of the outer vector of NetworkWeights is the same as the number of layers
	bool input = false;
	for (int i=0; i < NumberofLayers; i++){ //Iterates over the layers of the network
		Layers.push_back(layer(NetworkWeights.at(i), NetworkBias.at(i), input); //creates a vector of neurons using layer/constructor1 wich in turn uses neuron/constructor1
	}
}


//Constructor for the network class when random weights and biases are chosen
network::network(vector<int> nNeurons, int nInputs){
	NumberofLayers = nNeurons.size();
	bool input = false;	
	for(int i=0; i < NumberofLayers; i++){ //Iterates over the layers of the network
		Layers.push_back(layer(nNeuron.at(i), nInputs, input)) //creates a vector of neurons using layer/constructor2 wich in turn uses neuron/constructor2
	}

}

//Destructor
network::~network(){
}
//=================================================================================================

network::network(const network &net){
	Layers = net.Layers;
	NumberofLayers = net.NumberofLayers;
}

//Assignment operator?

//=================================================================================================

void network::setWeights(vector<vector<vector<float>>> NetworkWeights){

	//for(vector<vector<layer>>::iterator it=Layers.begin();it != Neurons.end(); it++){
		
	//}
	for(int i = 0; i < NetworkWeights.size(); i++){ //Iterates over the layers off the network
		layer::setWeights(NetworkWeights.at(i) //For every layer, sets the weights using the setWeighs function from the layer class
	}
}

void network::setBias(vector<vector<float>> NetworkBias){

	for(int i = 0; i < NetworkBias.size(); i++){ //Iterates over the layers off the network
		layer::setBias(NetworkBias.at(0); //For every layer, sets the weights using the setWeighs function from the layer class
	}
}

//void network::setNumberofLayers(int){
	//........
//}

void network::getWeights(){
	//........
}

void network::getBias(){
	//........
}

int network::getNumberofLayers(){
	return Layers.size();
}


