#pragma once

#include "Macros.h"
#include "Layer.h"

class Node;

class Network2
{

public:

	//	Network2(const std::vector<Layer>& sizes, const checker_type& f, int batchSize, double _learnRate, double maxRate, double minRate, double L2, double momentum);


	Network2(const std::vector<Layer*>& _layers, const checker_type& ch, int _in, int _out, int mbs, double lr);

	~Network2();

	void train(trbatch& data, trbatch& test, int numEpochs);

	void feedForward(Mat& input); // pass by reference. input layer will output as output layer

private:

	// functions
	Vec selfPlay(); // plays a game against itself, returns training data of MCTS probability distributions

	void simulate(Node* start); // go down the MCTS tree, based on moves chosen by the neural net
	
	// properties
	checker_type checker;

	// the layers in the network
	std::vector<Layer*> layers;

	int numLayers, in, out;

	int miniBatchSize;

	// how quickly it learns
	double learnRate, maxRate, minRate;

	// how much L2regularization affects cost
	// if high, it will focus on keeping weights low
	// if low, it will focus on minimizing regular cost function
	double L2;

	double momentum;

	// to track progress
	double maxfrac = 0;

	// random device class instance, source of 'true' randomness for initializing random seed
	std::random_device randDev;

	// Mersenne twister PRNG, initialized with seed from previous random device instance
	std::mt19937 randGen;
};