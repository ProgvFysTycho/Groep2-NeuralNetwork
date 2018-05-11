#include "Network.h"


//Author: Robbe (& Marjan)=========================================================================
//Constructor for the network class when Weights and biases are loaded from a file
network::network(const vector<vector<vector<float>>>& NetworkWeights, const vector<vector<float>>& NetworkBias)
{	
	//Possible argument check	

	NumberofLayers = NetworkWeights.size(); // The size of the outer vector of NetworkWeights is the same as the number of layers
	//bool input = false;
	for (int i=0; i < NumberofLayers; ++i)  // Iterates over the layers of the network
	{
		Layers.push_back(layer(NetworkWeights.at(i), NetworkBias.at(i)));	//creates a vector of neurons using layer/constructor1 wich in turn uses neuron/constructor1
	}
}

/*network::network(const string fileName)
{
	
	loadLayers(fileName);
	for (int i=0; i < NumberofLayers; ++i)  // Iterates over the layers of the network
	{
		Layers.push_back(layer(NetworkWeights.at(i), NetworkBias.at(i))); //creates a vector of neurons using layer/constructor1 wich in turn uses neuron/constructor1
	}
}*/


network::network(const vector<int>& nNeurons, const int nInputs)	//Constructor for the network class when random weights and biases are chosen
{
	NumberofLayers = nNeurons.size();
	//bool input = false;

	Layers.push_back(layer(nNeurons.at(0),nInputs));	// First layer of neurons (each neuron gets 'nInputs' input values) 
	for(int i=1; i < NumberofLayers; ++i)			//Iterates over the layers of the network
	{ 
		Layers.push_back(layer(nNeurons.at(i), nNeurons.at(i-1)));	//creates a vector of neurons using layer/constructor2 wich in turn uses neuron/constructor2
	}
}


network::~network()	//Destructor
{

}
//=================================================================================================

network::network(const network& net)	//Copy constructor
{ 
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

void network::setWeights(const vector<vector<vector<float>>>& NetworkWeights)	// sets weights for every layer
{

	int count = 0;
	for_each(Layers.begin(), Layers.end(),		// For each layer i in the 'Layers' vector
		[&](layer& Layer) {			// change their weights to one of layer i of 'NetworkWeights'.
			Layer.setWeights(NetworkWeights.at(count++));	// Here is the post-increment of 'count' usefull.
	});
}

void network::setBias(const vector<vector<float>>& NetworkBias)	// sets biases for every layer
{

	int count = 0;
	for_each(Layers.begin(), Layers.end(),		// For each layer i in the 'Layers' vector
		[&](layer& Layer) {			// change their biases to one of layer i of 'NetworkBias'.
			Layer.setBias(NetworkBias.at(count++));	// Here is the post-increment of 'count' usefull.
	});
}

void network::setNumberofLayers(const int NLayers)	// sets amount of layers in the network
{
	NumberofLayers = NLayers;
}

vector<vector<vector<float>>> network::getWeights()
{
	vector<vector<vector<float>>> weights;
	
	for(int i=0; i < NumberofLayers; ++i){
		weights.push_back((Layers.at(i)).getWeights());
	}
	return weights;
}

vector<vector<float>> network::getBias()
{
	vector<vector<float>> bias;
	for(int i=0; i < NumberofLayers; ++i){
		bias.push_back((Layers.at(i)).getBias());
	}
	return bias;
}

int network::getNumberofLayers() const
{
	return NumberofLayers;
}

void network::loadLayers(const string fileName) //Function to load already exsisting weights and bias
{
//Load values from a CSV-file as a vector of vectors of strings
        ifstream file(fileName);
        vector<vector<string>> dataString;
        vector<vector<vector<string>>> TotdataString;
        string line;
	string delimeter = ",";
	        // Iterate through each line and split the content using delimeter ","
	        while (getline(file, line))
	        {
	                vector<string> vec; //Temorary vector
	                boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
                        if(line.empty())
                        {
                                TotdataString.push_back(dataString);
                                dataString.clear();
                        } //If a empty line is found the program pushes the temporary vector<vector<string>> in the main object vectro<vector<vector<string>>> and clears the temporary storage object
                        else{
                                dataString.push_back(vec);
                        }
	        }
	        // Close the File
	        file.close();

//Transformation of strings to floats (vector<vector<string>> dataString => vector<vector<float>> dataFloat)
	vector<vector<vector<float>>> dataFloat; //Has the same structure as TotdataString
	for(vector<vector<string>> vecvec : TotdataString)
        { //iterates through each object in TotdataString and converts it to a float
                vector<vector<float>> FillFill;
                for(vector<string> vec : vecvec)
                {
        		vector<float> Fill;
                        for(string data : vec)
                        {
        			Fill.push_back(stof(data));
                        }
        		FillFill.push_back(Fill);
                }
                dataFloat.push_back(FillFill);
        }
                
        vector<float> Dimens = dataFloat.at(0).at(0);
	//int NInputs = Dimens.at(0);
	size_t NLayers1 = Dimens.at(1);
        size_t NLayers2 = Dimens.size()-2;

	//if(NLayers1 == NLayers2){
		setNumberofLayers(NLayers1); //Set the number of layers in the network
	/*}
	//else{
	//	cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "The first row of the loadfile is not consistent" << endl;
	}*/

        vector<vector<float>> NetworkBias = dataFloat.at(1);
	if(NetworkBias.size() == NLayers1)
	{
		setBias(NetworkBias); //Set the biases in the network
	}
	else{
		cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Not enough/too many biases for the amount of layers" << endl;
	}

        vector<vector<vector<float>>> NetworkWeights;
        for(int i=2; i< getNumberofLayers()+2; ++i)
        {
		if((dataFloat.at(i)).size() == Dimens.at(i))
		{
                	NetworkWeights.push_back(dataFloat.at(i));
		}
		else{
			cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Not enough/too many biases for the amount of neurons in layer " << i-1 << endl;
		}
        }

	if(NetworkWeights.size() == NLayers1)
	{
		setWeights(NetworkWeights);
	}
	else{
		cout << "Error: Dimensions of loadfile are incorrect" << "\n" << "Too many/Not enough weights for the number of layers" << endl;
	}
}


//Author: Tycho=========================================================================
void network::saveLayers(const string fileName)
{
    // check fileName
    const string extension(".csv");	// this must be the last part of the fileName
    const size_t lenghtExt = extension.size();
    const size_t lenghtFileName = fileName.size();
    if ((lenghtFileName <= lenghtExt) || ((fileName.substr(lenghtFileName-lenghtExt)) != extension)) // check if fileName is valid
    {
    	throw std::invalid_argument("\n network::saveLayers: invalid argument, argument must have extension 'csv'.\n");
    }
    
    
    const char* commaDelim = ",";	// used as delimiter between values in file
    const char* newLineDelim = "\n";	// end of line characters, used as delimiter between rows of values in file
    const size_t nInputs = getWeights().front().front().size(); // # weights of first neuron of first layer = # inputs of network
    
    // Begin of writing to file
    ofstream outFile(fileName);
        
    outFile << nInputs;	// prints # inputs of network to 'fileName' 
    outFile << commaDelim << getNumberofLayers();	// second value of first row of 'fileName' is # layers in network
    for_each(Layers.begin(),Layers.end(),[&](layer& Layer)	// For each layer i in the 'Layers' vector
    	{						
    		outFile << commaDelim << Layer.getNumberOfNeurons();	// prints # neurons to 'saveFile'
    	});	// & in [] so the variables 'saveFile' and 'commaDelim' are know in this print function.
    
    outFile << newLineDelim << newLineDelim;	// add an empty line to saveFile
    
    // printing BIAS values to file
    for_each(Layers.begin(),Layers.end(),[&](layer& Layer)	// For each layer i in the 'Layers' vector
    	{						
    		const vector<float>& layerBias = Layer.getBias();		// temporarily vector to store the biases of layer i
    		copy(layerBias.begin(),layerBias.end()-1,
    			ostream_iterator<float>(outFile, commaDelim));	// print those biases to file 'saveFile'
    		outFile << layerBias.back() << newLineDelim;		// print bias of last neuron in layer i and start a new line in the file
    	});
    
    outFile << newLineDelim;	// second 'end of line character' in row -> add empty line in file

    // printing WEIGHTS values to file 
    for_each(Layers.begin(),Layers.end(),[&](layer& Layer)	// For each layer i in the 'Layers' vector
    	{
    		const vector<vector<float> >& layerWeights = Layer.getWeights();	// temporarily vector to store the weights of layer i
    		for_each(layerWeights.begin(),layerWeights.end(),[&](const vector<float>& neuronWeights)	// For each neuron j in layer i
    			{
    			copy(neuronWeights.begin(),neuronWeights.end()-1,
    				ostream_iterator<float>(outFile, commaDelim));	// print those weights to file 'saveFile'
    			outFile << neuronWeights.back() << newLineDelim;	// print weight of last neuron in layer i and start a new line in the file
    			});
    		outFile << newLineDelim;	// // second 'end of line character' in row -> add empty line in file
    	});
   // End of writing to file
    outFile.close();
}


//Author: Marjan & Yannick=========================================================================

vector<vector<float>> network::errorFunc(const vector<float>& y)	// calculates error function for given y and the previous calculated a
{   

	vector<vector<vector<float>>> W = getWeights();
	vector<vector<float>> B = getBias();
	vector<vector<float*>> A = LayerResult;   // Contains results of every layer, excluding input of first layer


//////// errorfunction of last layer
	cout << "Calculation error function last layer" << endl;
	vector<vector<float>> wll = W.at(NumberofLayers); 	// weights wjk between last j layer and second-last k layer
	vector<float> bll = B.at(NumberofLayers);		// bias last layer
 	vector<float*> all = A.at(NumberofLayers);		// Output last layer
	vector<float*> avl = A.at(NumberofLayers-1); 		// input last layer (output second last layer)
	vector<float> Dll;					// errorfunc last layer

	layer L = Layers.at(NumberofLayers);  // call last layer out of vector of layers
	for (unsigned int i=0; i<all.size(); ++i) // loop over neurons last layer
	{  
		neuron N = L.Neurons.at(i); // call i-th neuron out of vector of neurons of layer l
		N.setBias(bll.at(i)); // set bias of i-th neuron in layer l
		N.setWeights(wll.at(i)); // set weights of i-th neuron in layer l			
		N.activateFunc(avl);  // call activateFunc to calculate z 
		float x = (*all.at(i)-y.at(i))*N.dsigmoid(); // calculate errorfunction
		Dll.push_back(x); 
	}

//////// errorfunction of front layers by recursive prescription
	vector<float> Dl; // temporary storage for error function of one layer
	vector<vector<float>> DD = {Dll}; // error function: vector/layer
	vector<float*> A0; ////// Hoe wordt deze meegegeven???
	for (signed int l = NumberofLayers-2; l>=0; --l) // loop over #layers starting at second last, l=layer
	{ 
		cout << "Calculation error function for layer " << l+1 << endl;
		Dl.clear();  //  clear temporary storage
		layer L = Layers.at(l);  // call l-th layer out of vector of layers
		if (l != 0)
		{
			for (unsigned int i=0; i<A.at(l).size(); ++i) //loop over #neurons per layer, i=neuron
			{  
				neuron N = L.Neurons.at(i); // call i-th neuron out of vector of neurons of layer l
				N.setBias(B.at(l).at(i)); // set bias of i-th neuron in layer l
				N.setWeights(W.at(l).at(i)); // set weights of i-th neuron in layer l	
				N.activateFunc(A.at(l-1)); // calculate z with input of layer l

				float WD = 0;		
				for (unsigned int j=0; j<DD.at(l+1).size(); ++j) // vector multiplication of Wkj*D(l+1)
				{
					WD = WD + W.at(l+1).at(j).at(i) * DD.at(0).at(j);  // use always first vector of DD
				}

				Dl.push_back(WD * N.dsigmoid()); // add errorfunc for i-th neuron to Dl
			}
		}
		else{ // calculation for first layer, use A0
			for (unsigned int i=0; i<A.at(l).size(); ++i) //loop over #neurons per layer, i=neuron
			{  
				neuron N = L.Neurons.at(i); // call i-th neuron out of vector of neurons of layer l
				N.setBias(B.at(l).at(i)); // set bias of i-th neuron in layer l
				N.setWeights(W.at(l).at(i)); // set weights of i-th neuron in layer l	
				N.activateFunc(A0); // calculate z with input of layer l

				float WD = 0;		
				for (unsigned int j=0; j<DD.at(l+1).size(); ++j) // vector multiplication of Wkj*D(l+1)
				{  
					WD = WD + W.at(l+1).at(j).at(i) * DD.at(0).at(j);  // use always first vector of DD
				}
				Dl.push_back(WD * N.dsigmoid()); // add errorfunc for i-th neuron to Dl
			}
			
		}
		DD.insert(DD.begin(), Dl);  // add errorfunc for l-th layer in front of DD
	}
	return DD;
}


vector<float*> network::resultFunc(const vector<float*>& Input)	// calculates the result of the last layer 
{  

	LayerResult.clear(); // Clear layerresult vector
	vector<float*> result = Input; // Start for recursive function
	for (signed int l=0; l<NumberofLayers; ++l)  // loop over all layers
	{
		result = (Layers.at(l)).resultFunc(result);  // result of layer l+1
		LayerResult.push_back(result);  // add vector result to LayerResult
	}
	return result;
}


float network::costFunc(const vector<float>& a ,const vector<float>& y)  // Calculates cost function for given y and a. 
{ 
	float C = 0;
	for (unsigned int i=0; i<a.size(); ++i){
		C = C + pow(y.at(i)-a.at(i),2);
	}
	return C/2;
}





