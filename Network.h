#include"Neuron.h"
#include"NeuronLayer.h"


using namespace std;

class network{
	public:
		network(vector<vector<vector<float>>> NetworkWeights, vector<vector<float>> NetworkBias); //Constructor1, when weights and biases are loaded from a file.
		network(vector<int> nNeurons, int nInputs); //Constructor2, when no weights or biases are given. Paramters are # neurons for every layer, #inputs for the first layer of neurons, # layers.
		~network(); //Destructor
		network(const network &net); //Copy constructor

		void setWeights(vector<vector<vector<float>>> NetworkWeights);
		void setBias(vector<vector<float>> NetworkBias);
		//void setNumberofLayers(int);

		vector<vector<vector<float>>> getWeights();
		vector<vector<float>> getBias();
		int getNumberofLayers();

	protected:
		vector<layer> Layers;
		int NumberofLayers;

		//bool NetworkHasChanged  
