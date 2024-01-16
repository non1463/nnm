#include "layer.h"
#include <fstream>
#include <iostream>

#include <iostream>
#define print(e) std::cout<<e<<std::endl

double Linear(double x) { return x; }
double Relu(double x) { return std::max(0., x); }

double Linear_(double x) { return 1; }
double Relu_(double x) { return (x>=0.?1.:0.); }

void Layer::LoadActivation()
{
	switch (activationId)
	{
	case 0:
		ActivationFunction = &Linear; 
		ActivationDerivative = &Linear_;
		break;
	case 1:
		ActivationFunction = &Relu; 
		ActivationDerivative = &Relu_;
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

	activationId = activationId_;
	LoadActivation();

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


