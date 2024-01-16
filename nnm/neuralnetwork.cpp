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

	file.read((char*)&layersNum, sizeof(unsigned));

	delete[] layers;
	layers = new Layer[layersNum];

	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Load(file);
	}

	file.close();
}

void NeuralNetwork::Clear()
{
	for (unsigned i = 0; i < layersNum; i++)
	{
		layers[i].Clear();
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