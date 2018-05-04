#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "propagate.h"
using namespace std;

propagate::propagate(float Eta, int Size){ // constructor
    setEta(Eta);
    setMiniBatchSize(Size);
}

void propagate::setEta(float Eta){
    Eta=Eta;
}

float propagate::getEta(){
    return Eta;
}


void propagate::setMiniBatchSize(int Size){
    MiniBatchSize = Size;
}

int propagate::getMiniBatchSize(){
    return MiniBatchSize;
}

void propagate::propagateMiniBatch(){

    for (int i=0; i<BatchSize; i++){
        vector<float> a; // = getResult() oplossing uit neuraal netwerk
	vector<float> y; // wordt meegegeven met figuur 

    }


    	

}

void propagate::propagateEpoch(){

    srand(time(0));  // anders steeds dezelfde random shuffle

    //////// shuffle mat objects + cijfer in random volgorde
    vector<int> Numbers;  // vector met getallen 1-100
    for (int i=0; i<100; i++) {   // 100-> length batch
        Numbers.push_back(i+1);
    } 

    std::random_shuffle(Numbers.begin(), Numbers.end() ); // random shuffle

    /////// verplaats mat objecten : plaats i = Mat[Numbers[i]] batch? 
    // Batch object? Mat + vector (0 0 0 0 1 0 ...) of 5 ? 
    // vector maken van minibatch? ja/nee? 

    /////// print vector op scherm
    for (int i=0; i<100; i++){
	cout << Numbers[i] << '\n' << endl;
    }

    ////// loop over verschillende minibatches

    for (int i=1; i<4; i++){

    }
}

propagate::~propagate() // destructor
{
}


int main () {

    propagate prop(5,5);
    prop.propagateEpoch();

    return 0;

}
