#include<mcblas0.hpp>

#include<iostream>
#include<cstdlib>

//#include<malloc.h>


const size_t algSize=64;

float *salloc(const int size)
{
	if (size>0)
	{
		float *r=NULL;
		if (posix_memalign((void **)&r, algSize, size*sizeof(float)) == 0)
			return r;
	}
	return NULL;
}

double *dalloc(const int size)
{
	if (size>0)
	{
		double *r=NULL;
		if (posix_memalign((void **)&r, algSize, size*sizeof(double)) == 0)
			return r;
	}
	return NULL;
}

void sinit(const int size, float *x, float val, float incv)
{
	for (int i=0; i<size; ++i)
	{
		x[i] = val;
		val = val + incv;
	}
}
void dinit(const int size, double *x, double val, float incv)
{
	for (int i=0; i<size; ++i)
	{
		x[i] = val;
		val = val + incv;
	}
}


void sdump(const int size, float *x)
{
	std::cout << "[ ";
	for (int i=0; i<size-1; ++i)
	{
		std::cout << x[i] << ", ";
	}
	std::cout << x[size-1] << "\n";
}

// void ddump(const int size, double *x)
// {
// 	printf("[ ");
// 	for (int i=0; i<size-1; ++i)
// 	{
// 		printf("%4.4lf, ", x[i]);
// 	}
// 	printf("%4.4lf ]\n",x[size-1]);
// }

void sfree(float *x)
{
	free(x);
}
// void dfree(double *x)
// {
// 	free(x);
// }











float **mmsalloc(const int row, const int col)
{
	if (row>0)
	{
		float **r = new float * [row];
		for (int i=0; i<row; ++i)
		{
			r[i] = new float [col] ;
		}
		return r;
	}
	return NULL;
}
void mmsinit(const int row, const int col, float **x, float val, float incv)
{
	float v = val;
	for(int r=0; r<row; ++r)
	{
		for(int c=0; c<col; ++c)
		{
			x[r][c] = v;
			v = v + incv;
		}
	}
}

void mmsdump(const int row, const int col, float **x)
{
	std::cout << "[\n";
	for(int r=0; r<row; ++r)
	{
		std::cout << "  [ ";
		for(int c=0; c<col-1; ++c)
		{
			std::cout << x[r][c] << ", ";
		}
		std::cout << x[r][col-1] << "]\n";
	}
	std::cout << "]" << std::endl;
}

void mmsfree(float **x, const int row, const int col)
{
	for(int r = 0; r<row; ++r)
	{
		delete[] x[r];
	}
	delete[] x;
}
