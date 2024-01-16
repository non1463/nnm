#pragma once

#include "layer.h"
#include <string>

class NeuralNetwork
{
public:
	void Save(std::string path);
	void Load(std::string path);

private:
	Layer* layers;
	unsigned layersNumber;

};

