#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>
//#include "propagate.h"
using namespace std;


float sigmoid(float z)   // sigmoid functie
{
        return 1/(1+exp(-z));
}


float dsigmoid(float z)   // afgeleide sigmoid functie
{
	float l = sigmoid(z);
        return l*(1-l);
}

vector<vector<float>> errorFunc(vector<float> y ,vector<vector<float>> A){   // berekent error functie voor een gegeven y en de berekende a

	//////// TESTwaardes voor 3 lagen: input1 = 4: dan 3/3/2 neuronen
	vector<float> Dll(2,0); // error functie laatste laag
	vector<float> w21 = {1,2,3}; // = w11
	vector<float> w22 = {4,5,6}; // = w12
	vector<float> w13 = {7,8,9};
	vector<float> w2 = {1,2};
	vector<vector<vector<float>>> W = {{w21,w22,w13},{w21, w22, w13},{w22,w22}}; // weights; matrix per laag (vector/neuron) 
        vector<vector<float>> B = {{1,1,1},{1,1,1},{1,1}}; // bias; vector per laag (1/neuron)  
	float z;     

	vector<float> a0 = {0.1,0.2,0.3,0.9}; // input begin

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
				WA = WA+ W.at(l).at(i).at(j)*A.at(l-1).at(j);
			}
			z = WA + B.at(l).at(i); 

			for (unsigned int j=0; j<DD.at(l+1).size(); j++){  // vectorvermeningvuldiging van Wkj*D(l+1)
				WD = WD + W.at(l+1).at(j).at(i)*DD.at(l+1).at(j);  
			}
			DD.at(l).at(i)= WD*dsigmoid(z);
			cout << DD.at(l).at(i) << endl;
		}
	}
	return DD;
}

vector<vector<float>> deriveBias(){

	vector<float> y = {0,1}; // wordt meegegeven met figuur -> meegegevenvector(inputvector)
        vector<float> a1={0.4,0.5,0.6};
	vector<float> a2={0.1,0.2,0.3};
        vector<float> a3={0.7,0.8};
	vector<vector<float>> A = {a1,a2,a3}; // output GetResult per laag (vector/laag) 
	vector<float> w21 = {1,2,3}; // = w11
	vector<float> w22 = {4,5,6}; // = w12
	vector<float> w13 = {7,8,9};
	vector<float> w2 = {1,2};
	vector<vector<vector<float>>> Weights = {{w21,w22,w13},{w21, w22, w13},{w22,w22}}; // weights; matrix per laag (vector/neuron) 
        vector<vector<float>> Bias = {{1,1,1},{1,1,1},{1,1}}; // bias; vector per laag (1/neuron)  
	float eta = 0.5;
	int NumberofLayers = 3;

	vector<vector<float>> newBias = Bias;
		
	vector<vector<float>> DD = errorFunc(y,A); // bereken error functie voor 1 figuur

	for (signed int l=0; l<NumberofLayers; l++){  // loop over alle layers
	cout << "Calculating new bias for layer " << l+1 << endl;
		for (signed int i=0; i<DD.at(l).size(); i++){  // loop over alle neuronen
			newBias.at(l).at(i) = Bias.at(l).at(i)-eta*DD.at(l).at(i);
			cout << newBias.at(l).at(i) << endl;
		}
	}
	return newBias;
}

vector<vector<vector<float>>> deriveWeights(){


	vector<float> y = {0,1}; // wordt meegegeven met figuur -> meegegevenvector(inputvector)
        vector<float> a1={0.4,0.5,0.6};
	vector<float> a2={0.1,0.2,0.3};
        vector<float> a3={0.7,0.8};
	vector<vector<float>> A = {a1,a2,a3}; // output GetResult per laag (vector/laag) 
	vector<float> w21 = {1,2,3}; 
	vector<float> w22 = {4,5,6}; 
	vector<float> w13 = {7,8,9};
	vector<float> w2 = {1,2};
	vector<vector<vector<float>>> Weights = {{w21,w22,w13},{w21, w22, w13},{w22,w22}}; // weights; matrix per laag (vector/neuron) 
        vector<vector<float>> Bias = {{1,1,1},{1,1,1},{1,1}}; // bias; vector per laag (1/neuron)  
	float eta = 0.5;
	int NumberofLayers = 3;

	vector<vector<vector<float>>> newWeights = Weights;
		
	vector<vector<float>> DD = errorFunc(y,A); // bereken error functie voor 1 figuur

	for (signed int l=1; l<NumberofLayers; l++){  // loop over alle layers
	cout << "Calculating new weights for layer " << l+1 << endl;
		for (signed int i=0; i<Weights.at(l).size(); i++){  // loop over alle neuronen
			for (signed int j=0; j<Weights.at(l).at(i).size(); j++){  // loop over alle inputs
				newWeights.at(l).at(i).at(j) = Weights.at(l).at(i).at(j) - eta*A.at(l-1).at(j)*DD.at(l).at(i);
				cout << newWeights.at(l).at(i).at(j) << endl;
			}
		}
	}
	return newWeights;
}


void propagateMiniBatch(){ 


}


int main () {
	vector<vector<float>> bias = deriveBias();
	vector<vector<vector<float>>> weights = deriveWeights();
 	return 0;

}

