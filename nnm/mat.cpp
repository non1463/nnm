#include "Mat.h"


Mat::Mat(unsigned size_) : size(size_)
{
	arr = new double* [size];
	for (unsigned i = 0; i < size; i++)
	{
		arr[i] = new double[size];
	}
}


void Mat::operator+= (Mat m)
{
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
		{
			arr[i][j] += m.arr[i][j];
		}
	}
}
void Mat::operator= (Mat m)
{
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
		{
			arr[i][j] = m.arr[i][j];
		}
	}
}
Mat Mat::operator* (Mat& m) // cross correlation
{
	Mat result(size - m.size + 1u);
	for (unsigned i = 0; i < result.size; i++)
	{
		for (unsigned j = 0; j < result.size; j++)
		{
			result.arr[i][j] = 0.;
			for (unsigned k = 0; k < m.size; k++)
			{
				for (unsigned l = 0; l < m.size; l++)
				{
					result.arr[i][j] += arr[i + k][j + l] * m.arr[k][l];
				}
			}
		}
	}
	return result;
}