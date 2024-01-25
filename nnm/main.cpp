#include <iostream>
#include <fstream>
#include <string>
#include "neuralnetwork.h"
#include "data.h"
#include "nnm.h"
using namespace std;

#define print(e) cout<<e<<endl
#define display(vect,n) for(int i=0;i<n;i++){cout<<vect[i]<<(i!=n-1?" / ":"");}cout<<endl;
#define last(vect) vect[vect.size()-1]

unsigned maxIndex(double* vect, unsigned n) { unsigned m = 0; double v = vect[0]; for (unsigned i = 1; i < n; i++) { if (vect[i] > v) { v = vect[i]; m = i; } }return m; }

NeuralNetwork nn;

void print_output(Point& p)
{
	double* output = nn.CalculateOutput(p.input);
	cout << "input : ";
	display(p.input, p.inputSize);
	cout << "output : ";
	display(output, p.outputSize);
	cout << "expect : ";
	display(p.output, p.outputSize);
	cout << "cost : " << nn.Cost(p) << endl;

	unsigned mxindex = maxIndex(output, p.outputSize);
	cout << "max index : " << mxindex << endl;
	double sum = 0.;
	for (unsigned i = 0; i < p.outputSize; i++)
	{
		sum += std::abs(output[i]);
	}
	cout << "confidence : " << output[mxindex]*100./sum << "%\n";
}


const unsigned layersNum = 3;
unsigned sz[layersNum] = { 1,100,1 };
char activation[layersNum-1] = { nnm::LINEAR, nnm::LINEAR };

double test[1] = { 1. };


Data dat(2ull, sz[0], sz[layersNum-1]);


vector<Point> points;
Point pt;



int main()
{
	nn.Load("nn/test.nn");
	dat.Load("data/test.dat");

	Batch fullBatch = dat.GetAllPointsBatch();

	int _ = 10000;
	while (_--)
	{
		nn.Learn(fullBatch, 0.2, 0.9);
	}


	Batch testBatch;
	testBatch.SetSize(1ull);

	char tmp = '*';
	while(tmp!='q')
	{
		dat.FillBatch(testBatch);

		print_output(*testBatch.arr[0]);
		cin >> tmp;
	}

	

	return 0;
}