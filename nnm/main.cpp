#include <iostream>
#include "neuralnetwork.h"
using namespace std;


NeuralNetwork nn;

int main()
{

	nn.Save("nn/test.nn");
	nn.Load("nn/test.nn");


	cout << "saved and loaded succesfully !" << endl;
	return 0;
}