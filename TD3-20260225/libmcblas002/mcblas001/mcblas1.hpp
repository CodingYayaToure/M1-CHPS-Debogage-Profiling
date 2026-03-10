#pragma once




/*
 * Routines of cblas level 1
 */
void sswap(const int size, float *x, const int incx,
		   float *y, const int incy);
void scopy(const int size, const float *x, const int incx,
		   float *y, const int incy);
void saxpy(const int size, const float alpha, const float *x,
		   const int incx, float *y, const int incy);

/* void dswap(const int size, double *x, const int incx, */
/* 		   double *y, const int incy); */
/* void dcopy(const int size, const double *x, const int incx, */
/* 		   double *y, const int incy); */
/* void daxpy(const int size, const double alpha, const double *x, */
/* 		   const int incx, double *y, const int incy); */
