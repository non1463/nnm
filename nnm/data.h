#pragma once

struct Point
{
	unsigned inputSize, outputSize;
	double* input;
	double* output;
};

struct Batch
{
	unsigned long long size;
	Point* set;
};

class Data
{

	unsigned long long size;
	Point* set;


};

