#include "../Headers/Layer.h"
#include "../Headers/FullyConnectedLayer.h"
#include "../Headers/Macros.h"

Layer::Layer() {}

Layer::~Layer() {
	//	printf("destroying layer\n");
}

Layer *read(ifstream &fin) {
	int layerType;
	fin >> layerType;
	if (layerType == 1) { // Fully connected layer
		return read_FC(fin);
	}
	else {
		cout << "Error in Layer.cpp: Invalid layer type when reading layer from file, layerType = " + to_string(layerType) + "\n";
		return nullptr;
	}
}
