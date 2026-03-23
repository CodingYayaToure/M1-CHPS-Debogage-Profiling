#include <mcblas3.hpp>
#include <immintrin.h>  // AVX2 + FMA intrinsics
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
    int r, c, d;
    int rr, cc, dd;
    const int Tr = 64;
    const int Tc = 64;
    const int Td = 64;

    // Vecteurs AVX constants
    __m256 vbeta  = _mm256_set1_ps(beta);
    __m256 valpha = _mm256_set1_ps(alpha);

    for (rr = 0; rr < m; rr += Tr)
    for (dd = 0; dd < k; dd += Td)
    for (cc = 0; cc < n; cc += Tc)
    for (r = rr; r < std::min(rr+Tr, m); ++r)
    for (d = dd; d < std::min(dd+Td, k); ++d)
    {
        // A(r,d) invariant sur c -> broadcast dans registre YMM
        __m256 vArd = _mm256_set1_ps(alpha * A(r,d));

        int c_end = std::min(cc+Tc, n);
        int c_end8 = cc + ((c_end - cc) / 8) * 8;

        // Boucle vectorisee : 8 floats par iteration (AVX2 256 bits)
        for (c = cc; c < c_end8; c += 8)
        {
            // Charger 8 elements de C(r,c) et B(d,c)
            __m256 vC = _mm256_loadu_ps(&C(r,c));
            __m256 vB = _mm256_loadu_ps(&B(d,c));

            // FMA : vC = vbeta*vC + vArd*vB  (1 instruction au lieu de 3)
            vC = _mm256_fmadd_ps(vArd, vB, _mm256_mul_ps(vbeta, vC));

            // Stocker le resultat
            _mm256_storeu_ps(&C(r,c), vC);
        }

        // Epilogue scalaire pour les elements restants (n % 8 != 0)
        for (c = c_end8; c < c_end; ++c)
            C(r,c) = beta * C(r,c) + alpha * A(r,d) * B(d,c);
    }
}
