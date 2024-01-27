#pragma once
struct Mat
{
	Mat(unsigned size_);

	double** arr;
	unsigned size;


	void operator+= (Mat m);
	void operator= (Mat m);
	Mat operator* (Mat& m); // cross correlation
};

