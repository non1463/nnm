#pragma once
#include <fstream>

#include "mat.h"

class Layer
{
public:
	Layer();
	~Layer();

	void Create(unsigned inputNodesNum, unsigned outputNodesNum, unsigned char activationFunc);
	void Save(std::ofstream& file);
	void Load(std::ifstream& file);
	void Clear();
	void Rand();

	double* CalculateOutput(double* input);

	double* CalculateNodeValues(double* val);
	double* CalculateHiddenNodeValues(Layer& oldLayer, double* val);
	void UpdateGradient(double* val);
	void ClearGradient();
	void ClearMomentumGradient();
	void ApplyGradient(double learnRate, double momentum);

	unsigned inputNodesNum, outputNodesNum;

	double* input; // not stored into the class (pointer to the output of the last layer)
	double* output;

private:
	double* biases;
	double** weights;

	double* costGradientB;
	double* momentumGradientB;
	double** costGradientW;
	double** momentumGradientW;
	
	unsigned char activationId;
	double (*ActivationFunction)(double);
	double (*ActivationDerivativeFromFunctionResult)(double); // /!\ calculate the derivative with the activation function result in argument 
	void LoadActivation();


	double NodeCost(double output, double expected_output);
	double NodeCostDerivative(double output, double expected_output);

};

class FullLayer : public Layer
{
private:

};

class ConvolutionLayer : public Layer
{
private:
	unsigned inputShape, kernelShape, outputShape;
};