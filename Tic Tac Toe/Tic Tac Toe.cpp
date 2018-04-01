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
	layers.push_back(new CustomLayer(50, 10));
	Network2 n(layers, check, 9, 10, 8, 0.5);
	*/
	ifstream fin;
	fin.open("file.txt");
	Network2 n;
	fin >> n;
	fin.close();
	n.train(500);
    return 0;
}


Vec binary(ll i, int bits)
{
	Vec v(bits);
	for (int j = 0; j < bits; ++j) {
		if (i & (1LL << j))
			v[j] = 1.0;
		else
			v[j] = 0.0;
	}
	return v;
}

Vec mod(long long i, int m) {
	Vec v = Vec::Zero(m);
	v[i % m] = 1.0;
	return v;
}
/*
int main() {
	srand(time(NULL));

	int bits = 13, m = 14;

	typedef FullyConnectedLayer<SigmoidActivationFunction> SigmoidLayer;
	typedef FullyConnectedLayer<SoftMaxActivationFunction> SoftMaxLayer;

	vector<Layer*> layers;
	layers.push_back(new SigmoidLayer(bits, 20 * bits));
	layers.push_back(new SoftMaxLayer(20 * bits, m));
	Network2 n(layers, check, bits, m, 16, 1);
	trbatch training(100000), testing(1000);

	for (trdata& data : testing) {
		ll i = rand() % (1 << bits);
//		ll j = rand() % (1 << bits);
//		data.first = binary((i << bits) + j, 2 * bits);
//		data.second = binary(i + j, bits + 1);
		data.first = binary(i, bits);
		data.second = mod(i, m);
	}
	for (trdata& data : training) {
		ll i = rand() % (1 << bits);
//		ll j = rand() % (1 << bits);
//		data.first = binary((i << bits) + j, 2 * bits);
//		data.second = binary(i + j, bits + 1);
		data.first = binary(i, bits);
		data.second = mod(i, m);
	}

	n.train(training, testing, 500);
}
*/