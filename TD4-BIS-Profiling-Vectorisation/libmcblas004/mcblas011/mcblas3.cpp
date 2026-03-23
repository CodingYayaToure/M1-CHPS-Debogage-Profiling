#include <mcblas3.hpp>
#include <immintrin.h>
#include <omp.h>
#include <iostream>

#define A(r,c) A[r*k+c]
#define B(r,c) B[r*n+c]
#define C(r,c) C[r*n+c]

void ssgemm(
    int m, int n, int k,
    float alpha,
    float * __restrict__ A,
    float * __restrict__ B,
    float beta,
    float * __restrict__ C)
{
    const int Tr = 64;
    const int Tc = 64;
    const int Td = 64;

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int rr = 0; rr < m; rr += Tr)
    for (int dd = 0; dd < k; dd += Td)
    for (int cc = 0; cc < n; cc += Tc)
    for (int r = rr; r < std::min(rr+Tr, m); ++r)
    for (int d = dd; d < std::min(dd+Td, k); ++d)
    {
        __m256 vbeta = _mm256_set1_ps(beta);
        __m256 vArd  = _mm256_set1_ps(alpha * A(r,d));
        int c_end  = std::min(cc+Tc, n);
        int c_end8 = cc + ((c_end - cc) / 8) * 8;
        for (int c = cc; c < c_end8; c += 8)
        {
            __m256 vC = _mm256_loadu_ps(&C(r,c));
            __m256 vB = _mm256_loadu_ps(&B(d,c));
            vC = _mm256_fmadd_ps(vArd, vB, _mm256_mul_ps(vbeta, vC));
            _mm256_storeu_ps(&C(r,c), vC);
        }
        for (int c = c_end8; c < c_end; ++c)
            C(r,c) = beta * C(r,c) + alpha * A(r,d) * B(d,c);
    }
}
