#include "layer.h"
#include <fstream>

#define deleteAllArrays delete[] biases;delete[] costGradientB;delete[] momentumGradientB;delete[] output;delete[] weightedInput;for (unsigned in = 0; in < inputNodesNum; in++){delete[] weights[in];delete[] costGradientW[in];delete[] momentumGradientW[in];}delete[] weights;delete[] costGradientW;delete[] momentumGradientW;
#define createAllArrays biases = new double[outputNodesNum];costGradientB = new double[outputNodesNum];momentumGradientB = new double[outputNodesNum];output = new double[outputNodesNum];weightedInput = new double[outputNodesNum];weights = new double* [inputNodesNum];costGradientW = new double* [inputNodesNum];momentumGradientW = new double* [inputNodesNum];for (unsigned in = 0; in < inputNodesNum; in++){weights[in] = new double[outputNodesNum];costGradientW[in] = new double[outputNodesNum];momentumGradientW[in] = new double[outputNodesNum];}


#include <iostream>
#define print(e) std::cout<<e<<std::endl

double Linear(double x) { return x; }
double Relu(double x) { return std::max(0., x); }
// tanh alredy defined
double Sigmoid(double x) { return 1. / (1. + exp(-x)); }
double Elu(double x) { return x<=0?exp(x)-1.:x; }

double Linear_(double x) { return 1.; } // /!\ calculate the derivative with the activation function result in argument 
double Relu_(double x) { return (x!=0.?1.:0.); }
double Tanh_(double x) { return 1. - (x * x); }
double Sigmoid_(double x) { return x * (1. - x); }
double Elu_(double x) { return x < 0. ? x+1. : 1.; }

void Layer::LoadActivation()
{
	switch (activationId)
	{
	case 0:
		ActivationFunction = &Linear; 
		ActivationDerivativeFromFunctionResult = &Linear_;
		break;
	case 1:
		ActivationFunction = &Relu; 
		ActivationDerivativeFromFunctionResult = &Relu_;
		break;
	case 3:
		ActivationFunction = &tanh;
		ActivationDerivativeFromFunctionResult = &Tanh_;
		break;
	case 4:
		ActivationFunction = &Sigmoid;
		ActivationDerivativeFromFunctionResult = &Sigmoid_;
		break;
	case 5:
		ActivationFunction = &Elu;
		ActivationDerivativeFromFunctionResult = &Elu_;
		break;
	}
}


double Layer::NodeCost(double output, double expected_output)
{
	double error = output - expected_output;
	return error * error;
}

double Layer::NodeCostDerivative(double output, double expected_output)
{
	return 2 * (output - expected_output);
}


Layer::Layer()
{
	inputNodesNum = 1u;
	outputNodesNum = 1u;

	activationId = 0;
	LoadActivation();

	createAllArrays
}

Layer::~Layer()
{
	deleteAllArrays
}


void Layer::Create(unsigned inputNodesNum_, unsigned outputNodesNum_, char activationId_)
{
	// load activation function
	activationId = activationId_;
	LoadActivation();

	// clear old arrays
	deleteAllArrays

	// define new sizes
	inputNodesNum = inputNodesNum_;
	outputNodesNum = outputNodesNum_;

	// redefine arrays
	createAllArrays
}



void Layer::Save(std::ofstream& file)
{
	/* FILE FORMAT

	activationFunc (char)
	inputNodesNum (unsigned)
	outputNodesNum (unsigned)
	biases (double)*out
	weights (double)*in*out

	*/

	file.write((char*)&activationId, sizeof(char));
	file.write((char*)&inputNodesNum, sizeof(unsigned));
	file.write((char*)&outputNodesNum, sizeof(unsigned));



	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		file.write((char*)&biases[out], sizeof(double));
	}

	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		for (unsigned out = 0; out < outputNodesNum; out++)
		{
			file.write((char*)&weights[in][out], sizeof(double));
		}
	}

}



void Layer::Load(std::ifstream& file)
{
	/* FILE FORMAT

	activationFunc (char)
	inputNodesNum (unsigned)
	outputNodesNum (unsigned)
	biases (double)*out
	weights (double)*in*out

	*/

	// load activation function
	file.read((char*)&activationId, sizeof(char));
	LoadActivation();

	// clear old arrays
	deleteAllArrays


	// load sizes
	file.read((char*)&inputNodesNum, sizeof(unsigned));
	file.read((char*)&outputNodesNum, sizeof(unsigned));

	// redefine arrays
	createAllArrays

	// read values
	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		file.read((char*)&biases[out], sizeof(double));
	}

	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		for (unsigned out = 0; out < outputNodesNum; out++)
		{
			file.read((char*)&weights[in][out], sizeof(double));
		}
	}

}

void Layer::Clear()
{
	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		biases[out] = 0.;
		for (unsigned in = 0; in < inputNodesNum; in++)
		{
			weights[in][out] = 0.;
		}
	}
}



double* Layer::CalculateOutput(double* input_)
{
	input = input_;
	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		weightedInput[out] = biases[out];
		for (unsigned in = 0; in < inputNodesNum; in++)
		{
			weightedInput[out] += weights[in][out] * input[in];
			output[out] = ActivationFunction(weightedInput[out]);
		}
	}
	return output;
}



double* Layer::CalculateNodeValues(double* val)
{
	double* newVal;
	newVal = new double[outputNodesNum];

	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		newVal[out] = NodeCostDerivative(weightedInput[out], val[out]) * ActivationDerivativeFromFunctionResult(output[out]);
	}

	return newVal;
}

double* Layer::CalculateHiddenNodeValues(Layer& oldLayer, double* val)
{
	double* newVal;
	newVal = new double[outputNodesNum];

	for (unsigned inew = 0; inew < outputNodesNum; inew++)
	{
		newVal[inew] = 0.;
		for (unsigned iold = 0; iold < oldLayer.outputNodesNum; iold++)
		{
			newVal[inew] += oldLayer.weights[inew][iold] * val[iold];
		}
		newVal[inew] *= ActivationDerivativeFromFunctionResult(output[inew]);
	}

	delete[] val;
	return newVal;
}


void Layer::UpdateGradient(double* val)
{
	for (int out = 0; out < outputNodesNum; out++)
	{
		costGradientB[out] += val[out];
		for (int in = 0; in < inputNodesNum; in++)
		{
			costGradientW[in][out] += input[in] * val[out];
		}
	}
}

void Layer::ClearGradient()
{
	for (int out = 0; out < outputNodesNum; out++)
	{
		costGradientB[out] = 0.;
		for (int in = 0; in < inputNodesNum; in++)
		{
			costGradientW[in][out] = 0.;
		}
	}
}

void Layer::ClearMomentumGradient()
{
	for (int out = 0; out < outputNodesNum; out++)
	{
		momentumGradientB[out] = 0.;
		for (int in = 0; in < inputNodesNum; in++)
		{
			momentumGradientW[in][out] = 0.;
		}
	}
}

void Layer::ApplyGradient(double learnRate, double momentum)
{
	for (int out = 0; out < outputNodesNum; out++)
	{
		momentumGradientB[out] = momentum * momentumGradientB[out] + (1 - momentum) * costGradientB[out];
		biases[out] -= momentumGradientB[out] * learnRate;
		for (int in = 0; in < inputNodesNum; in++)
		{
			momentumGradientW[in][out] = momentum * momentumGradientW[in][out] + (1 - momentum) * costGradientW[in][out];
			weights[in][out] -= momentumGradientW[in][out] * learnRate;
		}
	}
}
