#include "Macros.h"
#include "FullyConnectedLayer.h"
#include "ActivationFunction.h"
#include "Neural Net.h"

typedef FullyConnectedLayer<SigmoidActivationFunction> SigmoidLayer;
typedef FullyConnectedLayer<SoftMaxActivationFunction> SoftMaxLayer;
typedef FullyConnectedLayer<CustomActivationFunction> CustomLayer;

pair<int, double> check(const Mat& tocheck, const Mat& correct)
{
	if (tocheck.rows() != correct.rows() || tocheck.cols() != correct.cols()) {
		printf("ERROR in check: Vectors are different sizes\n");
		return make_pair(0, 0);
	}
	int count = 0;
	double cost = 0.0;
	for (int col = 0; col < tocheck.cols(); col++)
	{
		bool works = true;
		double colCost = 0, max = 0;
		for (int i = 0; i < tocheck.rows(); ++i) {
//			double error = abs(tocheck(i, col) - correct(i, col));
//			if (error >= 0.5)
//				works = false;
//			cost += error * error;
			colCost += -correct(i, col)*log(tocheck(i, col));
			if (tocheck(i, col) > tocheck(max, col))
				max = i;
		}
		if (correct(max, col))
			++count;
		cost += colCost;
	}
	return make_pair(count, cost / tocheck.cols());
}

// decides whether the state is an end state, and if so, who the winner is
// specialized for the game of tic tac toe
pair<bool, double> eval(Vec state) {
	// check for 3 in a rows
	for (int i = 0; i < 3; i++) {
		if (state(3 * i) == state(3 * i + 1) && state(3 * i + 1) == state(3 * i + 2)) {
			if (state(3 * i) != 0)
				return make_pair(true, state(3 * i));
		}
		if (state(i) == state(i + 3) && state(i + 3) == state(i + 6)) {
			if (state(i) != 0)
				return make_pair(true, state(i));
		}
	}
	if (state(0) == state(4) && state(4) == state(8)) {
		if (state(0) != 0)
			return make_pair(true, state(0));
	}
	if (state(2) == state(4) && state(4) == state(6)) {
		if (state(2) != 0)
			return make_pair(true, state(2));
	}
	// no 3 in a rows found
	for (int i = 0; i < 9; i++) {
		if (state(i) == 0) // available move
			return make_pair(false, 0);
	}
	return make_pair(true, 0); // tie
}

int main()
{
	srand(time(NULL));
	/*
	vector<Layer*> layers;
	layers.push_back(new SigmoidLayer(stateSize, 100));
	layers.push_back(new SigmoidLayer(100, 100));
	layers.push_back(new CustomLayer(100, maxMoves+1));
	Network2 n("Connect4 1 (100-100)", layers, check, stateSize, maxMoves+1, 16, 0.5);
	*/
	Network2 n("Connect4 1 (100-100)");

//	n.play();

	n.train(1000);
	cout << "Done!\n";
    return 0;
}