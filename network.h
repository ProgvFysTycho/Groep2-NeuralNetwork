
#ifndef NETWORK_H
#define NETWORK_H

#include <string>
using std::string;

#include <vector>
using std::vector;

class network
{
	public:
		network(int nlayers, int nNeurons[], vector<vector<vector<float> > >& inputWeights, vector<vector<float> >& inputBias);	// Constructor
		~network();			// Destructor
	
		void setWeights(const vector<vector<vector<float> > >& inputWeights);	
		void setBias(const vector<vector<float> >& inputBias);
		void setNumberOfLayers(const int nlayers);	
		
		void setLayerNneurons(int nNeurons[]);	// This function is for the test data member 'layer'
		
		int getNumberOfLayers() const;
		
		
		void saveLayers(const string filename) const;	// This function saves the current values of all the biases and weights in the network
								// in a text file with name 'filename'.  	

	protected:
		
		int NumberOfLayers;
		
		
		vector<vector<float> > TestBias;
		vector<vector<vector<float>>> TestWeights;
		
		// Test data member: a 'dummy' layer
		struct layer{
		int Nneurons;
		vector<vector<float> > Weights;
		vector<float> Bias;
		};
		vector<layer> Layers;

};

#endif // NETWORK_H

