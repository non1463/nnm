#include "layer.h"
#include <fstream>
#include <iostream>

#include <iostream>
#define print(e) std::cout<<e<<std::endl


Layer::Layer()
{
	inputNodesNum = 1u;
	outputNodesNum = 1u;
	activationFunc = 0;

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


void Layer::Create(unsigned inputNodesNum_, unsigned outputNodesNum_, char activationFunc_)
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
	activationFunc = activationFunc_;

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

	file.write((char*)&activationFunc, sizeof(char));
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

	// clear old arrays
	delete[] bias;
	delete[] output;
	for (unsigned in = 0; in < inputNodesNum; in++)
	{
		delete[] weights[in];
	}
	delete[] weights;

	// load sizes
	file.read((char*)&activationFunc, sizeof(char));
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
		}
	}
	return output;
}


