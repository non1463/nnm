#include <iostream>
#include "neuralnetwork.h"
using namespace std;

#define print(e) cout<<e<<endl
#define display(vect,n) for(int i=0;i<n;i++){cout<<vect[i]<<(i!=n-1?" / ":"");}cout<<endl;

unsigned maxIndex(double* vect, unsigned n) { unsigned m = 0; double v = vect[0]; for (int i = 1; i < n; i++) { if (vect[i] > v) { v = vect[i]; m = i; } }return m; }

void print_output(double* output, unsigned n)
{
	cout << "output : ";
	display(output, n);
	cout << "max index : " << maxIndex(output, n) << endl;
}

unsigned sz[3] = { 4,3,5 };
char activation[2] = { 0,0 };

double test[4] = { 3.,1.,4.,1. };
double* output;

NeuralNetwork nn;


int main()
{


	nn.Create(3, sz, activation);
	nn.Clear();
	nn.Save("nn/test.nn");


	output = nn.CalculateOutput(test);

	print_output(output, 5);


	return 0;
}