#include "layer.h"
#include <fstream>

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
	file.read((char*)&activationFunc, sizeof(char));
	file.read((char*)&inputNodesNum, sizeof(unsigned));
	file.read((char*)&outputNodesNum, sizeof(unsigned));

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