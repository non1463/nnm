#pragma once
#include <fstream>

class Layer
{
public:
	Layer();
	~Layer();

	void Create(unsigned inputNodesNum, unsigned outputNodesNum, char activationFunc);
	void Save(std::ofstream& file);
	void Load(std::ifstream& file);
	void Clear();

	double* CalculateOutput(double* input);



private:
	unsigned inputNodesNum = 0u, outputNodesNum = 0u;

	double* bias;
	double** weights;

	double* output;

	char activationId; // 0->Linear, 1->Relu, 2->
	double (*ActivationFunction)(double);
	double (*ActivationDerivativeFromFunctionResult)(double); // /!\ calculate the derivative with the activation function result in argument 
	void LoadActivation();


};

