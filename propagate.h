#ifndef propagate_H
#define propagate_H

#include <vector>

class propagate{
	public:
		propagate(float,int); // constructor

		void propagateEpoch();

		void setEta(float);
		float getEta();

		void setMiniBatchSize(int);
		int getMiniBatchSize();

		//vector<vector<float>> deriveBias();
		//vector<vector<vector<float>>> deriveWeights();

		~propagate(); // destructor

		// copyconstructor

	protected:
		void propagateMiniBatch();  
		

		int MiniBatchSize;
		float Eta;

		//batch TrainingBatch; uit class batch
	
};

#endif
