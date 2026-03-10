#include <mcblas1.hpp>

/*
 * Routines of cblas level 1
 */

void sswap(const int size, float *x, const int incx, float *y, const int incy)
{
	if ( (incx == 1) && (incy == 1) )
	{
		for (int i=0; i<size; ++i)
		{
			float tmp;
			tmp = x[i];
			x[i] = y[i];
			y[i] = tmp;
		}
	}
	else
	{
		for (int i=0; i<size; ++i)
		{
			int ix = 0;
			int iy = 0;
			float tmp;
			tmp = x[ix];
			x[ix] = y[iy];
			y[iy] = tmp;
			ix = ix + incx;
			iy = iy + incy;
		}
	}
}

void scopy(const int size, const float *x, const int incx, float *y, const int incy)
{
	if ( (incx == 1) && (incy == 1) )
	{
		for (int i=0; i<size; ++i)
		{
			y[i] = x[i];
		}
	}
	else
	{
		int ix = 0;
		int iy = 0;
		for (int i=0; i<size; ++i)
		{
			y[iy] = x[ix];
			ix = ix + incx;
			iy = iy + incy;
		}
	}
}

void saxpy(const int size, const float alpha, const float *x, const int incx, float *y, const int incy)
{

	if ( (incx == 1) && (incy == 1) )
	{
		for (int i=0; i<=size; ++i)
		{
			y[i] = y[i] + alpha * x[i];
		}
	}
	else
	{
		int ix = 0;
		int iy = 0;
		for (int i=0; i<size; ++i)
		{
			y[i] = y[i] + alpha * x[i];
			ix = ix + incx;
			iy = iy + incy;
		}
	}
}


/* void dswap(const int size, double *x, const int incx, double *y, const int incy) */
/* {} */

/* void dcopy(const int size, const double *x, const int incx, double *y, const int incy) */
/* {} */

/* void daxpy(const int size, const double alpha, const double *x, const int incx, double *y, const int incy) */
/* {} */
