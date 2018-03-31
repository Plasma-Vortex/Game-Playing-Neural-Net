#include "ActivationFunction.h"
#include "Macros.h"

static double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

static double sigmoidDeriv(double x) {
	return sigmoid(x)*(1-sigmoid(x));
}


static double tanhDeriv(double x) {
	return 1 - (tanh(x)*tanh(x));	
}

static double mytanh(double x) {return tanh(x);}
static double myexp(double x) {return exp(x);}

Mat SigmoidActivationFunction::activation(const Mat& x) {
	return x.unaryExpr(&sigmoid);
}
Mat SigmoidActivationFunction::activationDeriv(const Mat& x) {
	return x.unaryExpr(&sigmoidDeriv);
}

Mat TanhActivationFunction::activation(const Mat& x) {
	return x.unaryExpr(&mytanh);
}
Mat TanhActivationFunction::activationDeriv(const Mat& x) {
	return x.unaryExpr(&tanhDeriv);
}

Mat SoftMaxActivationFunction::activation(const Mat& x) {
	Mat y = x;
	for (int i = 0; i < y.cols(); i++) {
		double max = y(0, i);
		for (int j = 0; j < y.rows(); j++) {
			if (y(j, i) > max)
				max = y(j, i);
		}
		for (int j = 0; j < y.rows(); j++)
			y(j, i) -= max;
	}
	y = y.unaryExpr(&myexp);
	for (int c = 0; c < y.cols(); ++c)
		y.col(c) /= y.col(c).sum();
	return y;
}

Mat SoftMaxActivationFunction::activationDeriv(const Mat& x) {
	return Mat(1,1); // not actually used
}