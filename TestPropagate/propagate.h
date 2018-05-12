#ifndef PROPAGATE_H
#define PROPAGATE_H

#include <vector>

#include "Network.h"
#include "batch.h"


class propagate{
	public:
		propagate(float,int); // constructor
		~propagate(); // destructor
		// copyconstructor
		
		
		void setEta(float);
		void setMiniBatchSize(int);
		
		
		float getEta() const;
		int getMiniBatchSize() const;

		//vector<vector<float>> deriveBias();
		//vector<vector<vector<float>>> deriveWeights();

		
		void propagateEpoch();
		

	protected:
		void propagateMiniBatch();  
		
		
		int MiniBatchSize;
		float Eta;

		//network CurrentNetwork;
		//batch EvaluationBatch;
		//batch TrainingBatch; //uit class batch
	
};

#endif
