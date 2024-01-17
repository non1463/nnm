#include <iostream>
#include "neuralnetwork.h"
#include "data.h"
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

unsigned sz[3] = { 1,5,1 };
char activation[2] = { 0,0 };

double test[1] = { 1. };
double* output;

NeuralNetwork nn;

Data dat(2ull, 1u, 1u);
Batch fullBatch(dat.GetAllPointsBatch());


int main()
{

	dat.arr[0].input[0] = 0.;
	dat.arr[0].output[0] = 1.;

	dat.arr[1].input[0] = 1.;
	dat.arr[1].output[0] = 0.;

	dat.Save("data/test.dat");

	nn.Load("nn/test.nn");
	nn.Clear();

	unsigned _ = 0u;
	while (_--)
	{
		nn.Learn(fullBatch, 1., 0.);
	}

	output = nn.CalculateOutput(test);

	print_output(output, 1);

	cout << "expected : " << dat.arr[1].output[0] << endl;



	return 0;
}