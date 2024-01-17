#pragma once
#include <string>
#include <fstream>

class Point
{
public:
	Point();
	~Point();

	unsigned inputSize, outputSize;
	double* input;
	double* output;

	void SetSize(unsigned inputSize, unsigned outputSize);
	void Load(std::ifstream& file);
	void Save(std::ofstream& file);
};

class Batch
{
public:
	Batch();
	~Batch();

	void SetSize(unsigned long long size);

	unsigned long long size;
	Point** arr;
};

class Data
{
public:
	Data(unsigned long long size = 0ull, unsigned inputSize = 1u, unsigned outputSize = 1u);
	~Data();

	void Load(std::string path);
	void Save(std::string path);

	void FillBatch(Batch& batch);
	Batch GetAllPointsBatch();

	Point* arr;

private:
	unsigned long long size;
	unsigned inputSize, outputSize;
};

