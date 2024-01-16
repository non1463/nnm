#include <iostream>
#include "neuralnetwork.h"
using namespace std;


unsigned sz[3] = { 1,2,3 };
char activation[2] = { 0,0 };

NeuralNetwork nn;


int main()
{


	nn.Load("nn/test.nn");



	cout << "saved and loaded succesfully !" << endl;


	return 0;
}