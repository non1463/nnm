#pragma once

#include "layer.h"
#include <string>

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void Create(unsigned layersNum, unsigned* layerSize, char* layerActivation);
	void Save(std::string path);
	void Load(std::string path);
	void Clear();

	double* CalculateOutput(double* input);

private:
	Layer* layers;
	unsigned layersNum;

};

