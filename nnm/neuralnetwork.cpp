#include "neuralnetwork.h"
#include <string>
#include <fstream>


void NeuralNetwork::Save(std::string path)
{
	std::ofstream file(path, std::ios::out | std::ios::binary);

	file.write((char*)&layersNumber, sizeof(unsigned));

	for (unsigned i = 0; i < layersNumber; i++)
	{
		layers[i].Save(file);
	}

	file.close();

}

void NeuralNetwork::Load(std::string path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	file.read((char*)&layersNumber, sizeof(unsigned));

	for (unsigned i = 0; i < layersNumber; i++)
	{
		layers[i].Load(file);
	}

	file.close();

}