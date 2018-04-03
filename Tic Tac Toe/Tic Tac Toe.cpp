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

int main()
{
	srand(time(NULL));
	/*
	vector<Layer*> layers;
	layers.push_back(new SigmoidLayer(9, 50));
	layers.push_back(new SigmoidLayer(50, 50));
	layers.push_back(new CustomLayer(50, 10));
	Network2 n("Net4 (50-50)", layers, check, 9, 10, 16, 0.5);
	*/
	
	Network2 n("Net4 (50-50)");

//	n.play();

	n.train(1000);
	cout << "Done!\n";
    return 0;
}