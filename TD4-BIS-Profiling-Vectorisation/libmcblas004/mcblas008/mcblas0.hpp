#pragma once


/*
 * Routines of cblas level 0
 */
float *salloc(const int size);
double *dalloc(const int size);

void sinit(const int size, float *x, float val, float incv);
void dinit(const int size, double *x, double val, float incv);


void sdump(const int size, float *x);
void ddump(const int size, double *x);

void sfree(float *x);
void dfree(double *x);



float *mmsalloc(const int row, const int col);
void mmsinit(const int row, const int col, float *x, float val, float incv);
void mmsdump(const int row, const int col, float *x);
void mmsfree(float *x, const int row, const int col);



/* void sswap(const int size, float *x, const int incx, */
/* 		   float *y, const int incy); */
/* void scopy(const int size, const float *x, const int incx, */
/* 		   float *y, const int incy); */
/* void saxpy(const int size, const float alpha, const float *x, */
/* 		   const int incx, float *y, const int incy); */

/* void dswap(const int size, double *x, const int incx, */
/* 		   double *y, const int incy); */
/* void dcopy(const int size, const double *x, const int incx, */
/* 		   double *y, const int incy); */
/* void daxpy(const int size, const double alpha, const double *x, */
/* 		   const int incx, double *y, const int incy); */
