#include "neuralnetwork.h"
#include "layer.h"
#include <string>
#include <fstream>

#include <iostream>
#define print(e) std::cout<<e<<std::endl



NeuralNetwork::NeuralNetwork()
{
	layersNum = 1;
	layers = new Layer[1];

	ClearAllGradients();
	ClearAllMomentumGradients();
}

NeuralNetwork::~NeuralNetwork()
{
	delete[] layers;
}

void NeuralNetwork::Create(unsigned layersNum_, unsigned* layerSize, char* layerActivation)
{
	delete[] layers;

	layersNum = layersNum_ - 1;
	layers = new Layer[layersNum];

	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Create(layerSize[i], layerSize[i + 1], layerActivation[i]);
	}

	ClearAllGradients();
	ClearAllMomentumGradients();
}


void NeuralNetwork::Save(std::string path)
{
	std::ofstream file(path, std::ios::out | std::ios::binary);

	file.write((char*)&layersNum, sizeof(unsigned));

	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Save(file);
	}

	file.close();

}

void NeuralNetwork::Load(std::string path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	delete[] layers;

	file.read((char*)&layersNum, sizeof(unsigned));

	layers = new Layer[layersNum];

	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Load(file);
	}

	file.close();

	ClearAllGradients();
	ClearAllMomentumGradients();
}

void NeuralNetwork::Clear()
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Clear();
	}
}

void NeuralNetwork::Rand()
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Rand();
	}
}



double* NeuralNetwork::CalculateOutput(double* val)
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		val = layers[i].CalculateOutput(val);
	}
	return val;
}

void NeuralNetwork::UpdateAllGradients(Point& point)
{
	CalculateOutput(point.input);
	double* val;

	val = layers[layersNum - 1].CalculateNodeValues(point.output);
	layers[layersNum - 1].UpdateGradient(val);

	for (int i = (int)layersNum - 2; i >= 0; i--)
	{
		val = layers[i].CalculateHiddenNodeValues(layers[i + 1], val);
		layers[i].UpdateGradient(val);
	}
	delete[] val;
}

void NeuralNetwork::ClearAllGradients()
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].ClearGradient();
	}
}

void NeuralNetwork::ClearAllMomentumGradients()
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].ClearMomentumGradient();
	}
}

void NeuralNetwork::ApplyAllGradients(double learnRate, double momentum)
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].ApplyGradient(learnRate, momentum);
	}
}

void NeuralNetwork::Learn(Batch& batch, double learnRate, double momentum)
{
	for (unsigned long long i = 0; i < batch.size; i++)
	{
		UpdateAllGradients(*batch.arr[i]);
	}

	ApplyAllGradients(learnRate / ((double)batch.size), momentum);
	ClearAllGradients();
}


double NeuralNetwork::Cost(Point& point)
{
	double* output;
	output = CalculateOutput(point.input);

	double cost = 0.;
	double x;

	for (unsigned out = 0; out < point.outputSize; out++)
	{
		x = output[out] - point.output[out];
		cost += x * x;
	}
	return cost;
}

double NeuralNetwork::Cost(Batch& batch)
{
	double cost = 0.;
	for (unsigned long long i = 0; i < batch.size; i++)
	{
		cost += Cost(*batch.arr[i]);
	}
	return cost / (double)batch.size;
}