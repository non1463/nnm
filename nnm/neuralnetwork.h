#pragma once

#include "layer.h"
#include "data.h"
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

	void UpdateAllGradients(Point& point);
	void ClearAllGradients();
	void ClearAllMomentumGradients();
	void ApplyAllGradients(double learnRate, double momentum);
	void Learn(Batch& batch, double learnRate, double momentum);

private:
	Layer* layers;
	unsigned layersNum;

};

