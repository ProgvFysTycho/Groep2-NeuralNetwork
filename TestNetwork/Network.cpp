//#include"Neuron.h"
//#include"Layer.h"
#include "Network.h"

//#include <algorithm>// for copying vector content to savefile

//using namespace std;


//Author: Robbe (& Marjan)=========================================================================
//Constructor for the network class when Weights and biases are loaded from a file
network::network(vector<vector<vector<float>>> NetworkWeights, vector<vector<float>> NetworkBias){
	
	//Possible argument check	

	NumberofLayers = NetworkWeights.size(); //The size of the outer vector of NetworkWeights is the same as the number of layers
	//bool input = false;
	for (int i=0; i < NumberofLayers; ++i){ //Iterates over the layers of the network
		Layers.push_back(layer(NetworkWeights.at(i), NetworkBias.at(i)));	//creates a vector of neurons using layer/constructor1 wich in turn uses neuron/constructor1
	}
}


//Constructor for the network class when random weights and biases are chosen
network::network(const vector<int>& nNeurons, const int nInputs){
	NumberofLayers = nNeurons.size();
	//bool input = false;

	Layers.push_back(layer(nNeurons.at(0),nInputs)); // First layer of neurons (each neuron gets 'nInputs' input values) 
		for(int i=1; i < NumberofLayers; ++i){ //Iterates over the layers of the network
		Layers.push_back(layer(nNeurons.at(i), nNeurons.at(i-1)));	//creates a vector of neurons using layer/constructor2 wich in turn uses neuron/constructor2
	}
}

//Destructor
network::~network(){
}
//=================================================================================================

network::network(const network& net){ //Copy constructor
	Layers = net.Layers;
	NumberofLayers = net.NumberofLayers;
	//NetworkHasChanged  = net.NetworkHasChanged;
}

network& network::operator = (const network& net) //Assigment operator (constructor)
{
	if (&net != this)
	{
		Layers = net.Layers;
		NumberofLayers = net.NumberofLayers;
		//NetworkHasChanged  = net.NetworkHasChanged;
	}
	return *this;
}

//=================================================================================================

void network::setWeights(vector<vector<vector<float>>> NetworkWeights){

	//for(vector<vector<layer>>::iterator it=Layers.begin();it != Neurons.end(); it++){
		
	//}
	for(int i = 0; i < getNumberofLayers(); ++i){ //Iterates over the layers off the network
		(Layers.at(i)).setWeights(NetworkWeights.at(i)); //For every layer, sets the weights using the setWeighs function from the layer class
	}
}

void network::setBias(vector<vector<float>> NetworkBias){

	for(int i = 0; i < getNumberofLayers(); ++i){ //Iterates over the layers off the network
		(Layers.at(i)).setBias(NetworkBias.at(i)); //For every layer, sets the weights using the setWeighs function from the layer class
	}
}

void network::setNumberofLayers(int NLayers){
	NumberofLayers = NLayers;
}

vector<vector<vector<float>>> network::getWeights(){
	vector<vector<vector<float>>> weights;
	for(int i=0; i < NumberofLayers; ++i){
		weights.push_back((Layers.at(i)).getWeights());
	}
return weights;
}

vector<vector<float>> network::getBias(){
	vector<vector<float>> bias;
	for(int i=0; i < NumberofLayers; ++i){
		bias.push_back((Layers.at(i)).getBias());
	}
return bias;
}

int network::getNumberofLayers(){
	return Layers.size();
}

void network::loadLayers(const string fileName)
{
//De waarden uit de .CSV file inladen als string
        ifstream file(fileName);
        vector<vector<string>> dataString;
        vector<vector<vector<string>>> TotdataString;
        string line;
	string delimeter = ",";
	        // Iterate through each line and split the content using delimeter
	        while (getline(file, line))
	        {
	                vector<string> vec;
	                boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
                        if(line.empty()){
                                TotdataString.push_back(dataString);
                                dataString.clear();
                        }
                        else{
                                dataString.push_back(vec);
                        }
	        }
	        // Close the File
	        file.close();

        /*for(vector<vector<string>> vecvec: TotdataString){
                for(vector<string> vec: vecvec){
                        for(string data: vec){
                                cout << data << ",";
                        }
                cout << "\n";
                }
        cout << "\n";
        }*/
	

//Omzetten van strings naar floats (vector<vector<string>> dataString => vector<vector<float>> dataFloat)
	vector<vector<vector<float>>> dataFloat;
	for(vector<vector<string>> vecvec : TotdataString)
        {
                vector<vector<float>> FillFill;
                for(vector<string> vec : vecvec){
        		vector<float> Fill;
                        for(string data : vec){
        			Fill.push_back(stof(data));
                        }
        		FillFill.push_back(Fill);
                }
                dataFloat.push_back(FillFill);
        }
                
        vector<float> Dimens = dataFloat.at(0).at(0);
        int NLayers = Dimens.size()-1;

        vector<vector<float>> NetworkBias = dataFloat.at(1);

        vector<vector<vector<float>>> NetworkWeights;
        for(int i=2; i< NLayers+2; i++){
                NetworkWeights.push_back(dataFloat.at(i));
        }

        /*for(vector<vector<string>> vecvec : TotdataString){
                for(vector<string> vec : vecvec){
                        for(string data : vec){
                                cout << data << ",";
                        }
                        cout << "\n";
                }
                cout << "\n";
        }*/
}


//Author: Tycho=========================================================================
void network::saveLayers(const string fileName)
{
    // exception if the string 'filename' is invalid.
    const char* commaDelim = ",";	// used as delimiter between values in file
    const char* newLineDelim = "\n";	// end of line characters, used as delimiter between rows of values in file
     
    //cout << "Values of bias and weights of network will be printed to a file." << endl; // For testing
    //cout << "Filename is " << filename << "." << endl; // For testing
    
    const size_t nInputs = getWeights().front().front().size(); // # weights of first neuron of first layer = # inputs of network
    
    ofstream saveFile(fileName);
    // exception if file could not be opened.
     
     
    saveFile << nInputs;	// prints # inputs of network to 'fileName' 
    saveFile << commaDelim << getNumberofLayers();	// second value of first row of 'fileName'
    for (int i=0; i < NumberofLayers; ++i)
    {
    	saveFile << commaDelim << (Layers.at(i)).getNumberOfNeurons();
    }
    saveFile << newLineDelim << newLineDelim;
    
    // printing BIAS values to file
    vector<vector<float>> testBias = getBias();
    vector<vector<float> >::const_iterator endBiasNetwork = testBias.end(); 
    for (vector<vector<float> >::const_iterator iterLayer = testBias.begin() ; iterLayer != endBiasNetwork ; ++iterLayer)
    {
    	copy((*iterLayer).begin(),(*iterLayer).end()-1,ostream_iterator<float>(saveFile, commaDelim));
    	saveFile << (*iterLayer).back();
    	saveFile << newLineDelim;
    }
    saveFile << newLineDelim;
    
    // printing WEIGHTS values to file 
    vector<vector<vector<float>>> testWeights = getWeights();   
    vector<vector<vector<float> > >::const_iterator endWeightsNetwork = testWeights.end();
    for (vector<vector<vector<float> > >::const_iterator iterLayer = testWeights.begin() ; iterLayer != endWeightsNetwork ; ++iterLayer)
    {
    	vector<vector<float> >::const_iterator endWeightsLayer = (*iterLayer).end();
    	for (vector<vector<float> >::const_iterator iterNeuron = (*iterLayer).begin() ; iterNeuron != endWeightsLayer ;  ++iterNeuron)
    	{
    		copy((*iterNeuron).begin(),(*iterNeuron).end()-1,ostream_iterator<float>(saveFile, commaDelim));
    		saveFile << (*iterNeuron).back();
    		saveFile << newLineDelim;
    	}
    	saveFile << newLineDelim;
    }   
    
    
    saveFile.close();
}


//Author: Marjan & Yannick=========================================================================

/*
vector<vector<float>> network::errorFunc(vector<float> y){   // berekent error functie voor een gegeven y en de berekende a

	vector<vector<vector<float>>> W = getWeights();
	vector<vector<float>> B = getBias();
	vector<vector<float>> A = LayerResult;
//////// errorfunctie van laatste laag L. Uitkomsten D gechecked met matlab
	cout << "Calculation error function last layer" << endl;
	vector<vector<float>> wll = W.at(2); 	// weights wjk tussen laatste j en voorlaatste k laag 
	vector<float> bll = B.at(2);		// bias laatste laag
 	vector <float> all = A.at(2);		// Output laatste laag
	vector <float> avl = A.at(1); 		// input laatste laag (output voorlaatste laag)

	for (unsigned int i=0; i<all.size(); i++){  // loop over neuronen laatste laag
		float WA=0;
		for (unsigned int j=0; j<avl.size(); j++){  // vector vermenigvuldiging van Wjk*A(vl)
			WA = WA + wll.at(i).at(j)*avl.at(j);

		}
		z = WA + bll.at(i);

		Dll.at(i)=(all.at(i)-y.at(i))*dsigmoid(z); 
		cout << Dll.at(i) << endl;
	}

 	//////// errorfunctie voorliggende lagen via recursief voorschrift
	// Eerste laag maakt gebruik van a0 (de inputs) --> apart beschouwen?? z = wjk*a(l-1) + b
	vector<float> zero(3,0);
	int NumberofLayers = 3;
        vector<vector<float>> DD={zero,zero,Dll}; // error functie: vector/laag
	for (signed int l=NumberofLayers-2; l>0; --l){ // loop over #lagen van voorlaatste beginnende, l=laag, signed want anders werkt het niet (gaat niet onder 0) 
		cout << "Calculation error function for layer " << l+1 << endl;
		for (unsigned int i=0; i<A.at(l).size(); i++){  //loop over neuronen per laag, i=neuron
			float WA = 0;
			float WD = 0;
			for (unsigned int j=0; j<A.at(l-1).size(); j++){  // vectorvermenigvuldiging van W*A(l-1)
				WA = WA + W.at(l).at(i).at(j) * A.at(l-1).at(j);
			}
			z = WA + B.at(l).at(i); 

			for (unsigned int j=0; j<DD.at(l+1).size(); j++){  // vectorvermeningvuldiging van Wkj*D(l+1)
				WD = WD + W.at(l+1).at(j).at(i) * DD.at(l+1).at(j);  
			}
			DD.at(l).at(i) = WD * dsigmoid(z);
			cout << DD.at(l).at(i) << endl;
		}
	}
	return DD;
}


vector<float> network::resultFunc(vector<float> Input){  // berekent het resultaat van de laatste laag 

	//vector<layer> Layers;  // protected member uit class network
	//vector<float> resultFunc(Input); // roep resultfunc uit layer op
	vector<float> result = Input; // begin voor recursief voorschrift
	//vector<vector<float>> LayerResult;  // bevat alle result vectoren per laag --> protected member variabele
	for (unsigned int i=0; i<NumberofLayers; ++i){ // loop over alle lagen
		result = (Layers.at(i)).resultFunc(result);  // resultaat van laag i+1
		LayerResult.push_back(result);
	}
	return result;
}

float costFunc(vector<float> a ,vector<float> y ){  // berekent cost functie voor gegeven y en a. 
	float C = 0;
	for (unsigned int i=0; i<10; ++i){
		C = C + pow(y.at(i)-a.at(i),2);
	}

	return C/2;
}
*/



