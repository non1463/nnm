#include "layer.h"
#include <fstream>

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

Layer::Layer()
{
	inputNodesNum = 1u;
	outputNodesNum = 1u;

	activationId = 0;
	LoadActivation();

	bias = new double[1];
	output = new double[1];

	weights = new double* [1];
	weights[0] = new double[1];
}

Layer::~Layer()
{
	delete[] bias;
	delete[] output;
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		delete[] weights[in];
	}
	delete[] weights;
}


void Layer::Create(unsigned inputNodesNum_, unsigned outputNodesNum_, char activationId_)
{
 // load activation function
	activationId = activationId_;
	LoadActivation();

	// clear old arrays
	delete[] bias;
	delete[] output;
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		delete[] weights[in];
	}
	delete[] weights;

	// define new sizes
	inputNodesNum = inputNodesNum_;
	outputNodesNum = outputNodesNum_;

	// redefine arrays
	bias = new double[outputNodesNum];
	output = new double[outputNodesNum];

	weights = new double* [inputNodesNum];
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		weights[in] = new double[outputNodesNum];
	}
}



void Layer::Save(std::ofstream& file)
{
	/* FILE FORMAT

	activationFunc (char)
	inputNodesNum (unsigned)
	outputNodesNum (unsigned)
	bias (double)*out
	weights (double)*in*out

	*/

	file.write((char*)&activationId, sizeof(char));
	file.write((char*)&inputNodesNum, sizeof(unsigned));
	file.write((char*)&outputNodesNum, sizeof(unsigned));



	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		file.write((char*)&bias[out], sizeof(double));
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
	bias (double)*out
	weights (double)*in*out

	*/

	// load activation function
	file.read((char*)&activationId, sizeof(char));
	LoadActivation();

	// clear old arrays
	delete[] bias;
	delete[] output;
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		delete[] weights[in];
	}
	delete[] weights;

	// load sizes
	file.read((char*)&inputNodesNum, sizeof(unsigned));
	file.read((char*)&outputNodesNum, sizeof(unsigned));

	// redefine arrays
	bias = new double[outputNodesNum];
	output = new double[outputNodesNum];
	weights = new double* [inputNodesNum];
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		weights[in] = new double[outputNodesNum];
	}

	// load values
	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		file.read((char*)&bias[out], sizeof(double));
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
		bias[out] = 0.;
		for (unsigned in = 0; in < inputNodesNum; in++)
		{
			weights[in][out] = 0.;
		}
	}
}



double* Layer::CalculateOutput(double* input)
{
	for (unsigned out = 0; out < outputNodesNum; out++)
	{
		output[out] = bias[out];
		for (unsigned in = 0; in < inputNodesNum; in++)
		{
			output[out] += weights[in][out] * input[in];
			output[out] = ActivationFunction(output[out]);
		}
	}
	return output;
}


