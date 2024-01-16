#pragma once
#include <fstream>

class Layer
{
public:
	Layer();
	Layer(unsigned inputNodesNum, unsigned outputNodesNum, char activationFunc);
	~Layer();

	void Save(std::ofstream& file);
	void Load(std::ifstream& file);

	double* CalculateOutput(double* input);

private:
	unsigned inputNodesNum = 0u, outputNodesNum = 0u;

	double* bias;
	double** weights;

	double* output;

	char activationFunc;
};

