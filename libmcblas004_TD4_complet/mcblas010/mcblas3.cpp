#include <mcblas3.hpp>
#include <iostream>

/*
 * mcblas010 - Tiling + vectorisation AVX (boucle interne sur c, stride-1)
 * Q-4.1 : modification du blocking pour permettre la vectorisation
 * Bloc optimal T=64 : 3*64*64*4 = 49152 bytes < 64KB L1d
 */

#define A(r,c) A[(r)*k+(c)]
#define B(r,c) B[(r)*n+(c)]
#define C(r,c) C[(r)*n+(c)]

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

    if (alpha == 1.0f)
    {
        for (rr = 0; rr < m; rr += Tr)
        for (dd = 0; dd < k; dd += Td)
        for (cc = 0; cc < n; cc += Tc)
        for (r = rr; r < std::min(rr+Tr, m); ++r)
        for (d = dd; d < std::min(dd+Td, k); ++d)
        {
            float Ard = A(r,d);
            for (c = cc; c < std::min(cc+Tc, n); ++c)
                C(r,c) = C(r,c) * beta + Ard * B(d,c);
        }
    }
    else
    {
        for (rr = 0; rr < m; rr += Tr)
        for (dd = 0; dd < k; dd += Td)
        for (cc = 0; cc < n; cc += Tc)
        for (r = rr; r < std::min(rr+Tr, m); ++r)
        for (d = dd; d < std::min(dd+Td, k); ++d)
        {
            float aArd = alpha * A(r,d);
            for (c = cc; c < std::min(cc+Tc, n); ++c)
                C(r,c) = C(r,c) * beta + aArd * B(d,c);
        }
    }
}
