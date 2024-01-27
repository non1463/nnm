#include <iostream>
#include <fstream>
#include <string>
#include "neuralnetwork.h"
#include "data.h"
#include "nnm.h"
#include "mat.h"
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


//vector<Point> points;
Point pt;





const double inp_[9] = { 1,6,2,5,3,1,7,0,4 };
const double ker_[4] = { 1,2,-1,0 };



void print_matrix(Mat& mat)
{
	for (unsigned i = 0; i < mat.size; i++)
	{
		for (unsigned j = 0; j < mat.size; j++)
		{
			cout << mat.arr[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	Mat inp(3u);
	Mat ker(2u);
	Mat ou(2u);


	for (unsigned i = 0; i < inp.size; i++)
	{
		for (unsigned j = 0; j < inp.size; j++)
		{
			inp.arr[i][j] = inp_[j + inp.size * i];
		}
	}

	for (unsigned i = 0; i < ker.size; i++)
	{
		for (unsigned j = 0; j < ker.size; j++)
		{
			ker.arr[i][j] = ker_[j + ker.size * i];
		}
	}


	ou = inp * ker;
	

	print_matrix(ou);

	return 0;
}


