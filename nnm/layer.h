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

	double* CalculateNodeValues(double* val);
	double* CalculateHiddenNodeValues(Layer& oldLayer, double* val);
	void UpdateGradient(double* val);
	void ClearGradient();
	void ClearMomentumGradient();
	void ApplyGradient(double learnRate, double momentum);

	unsigned inputNodesNum = 0u, outputNodesNum = 0u;

	double* biases;
	double** weights;

	double* input; // not stored into the class (pointer to the output of the last layer)
	double* weightedInput;
	double* output;

private:
	double* costGradientB;
	double* momentumGradientB;
	double** costGradientW;
	double** momentumGradientW;

	char activationId; // 0->Linear, 1->Relu, 2->
	double (*ActivationFunction)(double);
	double (*ActivationDerivativeFromFunctionResult)(double); // /!\ calculate the derivative with the activation function result in argument 
	void LoadActivation();


	double NodeCost(double output, double expected_output);
	double NodeCostDerivative(double output, double expected_output);

};

