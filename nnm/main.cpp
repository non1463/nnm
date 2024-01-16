#include <iostream>
#include "neuralnetwork.h"
using namespace std;


unsigned sz[3] = { 1,2,3 };
char activation[2] = { 0,0 };

double test[1] = { 0. };

NeuralNetwork nn;


int main()
{


	nn.Create(3, sz, activation);
	nn.Clear();
	nn.Save("nn/test.nn");


	cout << nn.CalculateOutput(test)[0] << endl;


	return 0;
}