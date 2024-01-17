#include "data.h"
#include <string>
#include <fstream>

#include <iostream>
#define print(e) std::cout<<e<<std::endl

unsigned long long rn = 0ull;

void XorShift64()
{
	rn ^= rn << 13;
	rn ^= rn >> 7;
	rn ^= rn << 17;
}

///////////////////////POINT
Point::Point()
{
	inputSize = 0u;
	outputSize = 0u;

	input = new double[inputSize];
	output = new double[outputSize];
}

void Point::SetSize(unsigned inputSize_, unsigned outputSize_)
{
	delete[] input;
	delete[] output;

	inputSize = inputSize_;
	outputSize = outputSize_;

	input = new double[inputSize];
	output = new double[outputSize];
}

Point::~Point()
{
	delete[] input;
	delete[] output;
}

void Point::Load(std::ifstream& file)
{
	for (unsigned i = 0; i < inputSize; i++)
	{
		file.read((char*)&input[i], sizeof(double));
	}
	for (unsigned i = 0; i < outputSize; i++)
	{
		file.read((char*)&output[i], sizeof(double));
	}
}

void Point::Save(std::ofstream& file)
{
	for (unsigned i = 0; i < inputSize; i++)
	{
		file.write((char*)&input[i], sizeof(double));
	}
	for (unsigned i = 0; i < outputSize; i++)
	{
		file.write((char*)&output[i], sizeof(double));
	}
}


///////////////////////BATCH
Batch::Batch()
{
	arr = new Point * [1];
	arr[0] = nullptr;

	size = 1ull;
}

Batch::~Batch()
{
	delete[] arr;
}

void Batch::SetSize(unsigned long long size_)
{
	delete[] arr;

	size = size_;

	arr = new Point * [size];
}


///////////////////////DATA
Data::Data(unsigned long long size_, unsigned inputSize_, unsigned outputSize_)
{
	size = size_;
	inputSize = inputSize_;
	outputSize = outputSize_;

	delete[] arr;
	arr = new Point[size];

	for (unsigned long long i = 0; i < size; i++)
	{
		arr[i].SetSize(inputSize, outputSize);
	}
}

Data::~Data()
{
	delete[] arr;
}


void Data::FillBatch(Batch& batch)
{
	for (unsigned long long i = 0; i < batch.size; i++)
	{
		XorShift64();
		batch.arr[i] = &arr[rn%size];
	}
}

Batch Data::GetAllPointsBatch()
{
	Batch batch;

	batch.SetSize(size);

	for (unsigned long long i = 0; i < size; i++)
	{
		batch.arr[i] = &arr[i];
	}
	return batch;
}


void Data::Load(std::string path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	/* FILE FORMAT
	
	data_size (unsigned long long)
	input size (unsigned)
	output size (unsigned)

	points input + points output (double)*(input_sz+output_sz)

	*/
	// delete old array
	delete[] arr;


	// update sizes
	file.read((char*)&size, sizeof(unsigned long long));
	file.read((char*)&inputSize, sizeof(unsigned));
	file.read((char*)&outputSize, sizeof(unsigned));


	// resize array
	arr = new Point[size];


	// load info
	for (unsigned long long i = 0; i < size; i++)
	{
		arr[i].SetSize(inputSize, outputSize);
		arr[i].Load(file);
	}


	file.close();
}

void Data::Save(std::string path)
{
	std::ofstream file(path, std::ios::out | std::ios::binary);
	/* FILE FORMAT

	data_size (unsigned long long)
	input size (unsigned)
	output size (unsigned)

	points input + points output (double)*(input_sz+output_sz)

	*/

	file.write((char*)&size, sizeof(unsigned long long));
	file.write((char*)&inputSize, sizeof(unsigned));
	file.write((char*)&outputSize, sizeof(unsigned));


	for (unsigned long long i = 0; i < size; i++)
	{
		arr[i].Save(file);
	}


	file.close();
}