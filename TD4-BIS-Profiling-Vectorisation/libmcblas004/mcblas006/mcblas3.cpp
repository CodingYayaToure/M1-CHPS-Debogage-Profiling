#include <mcblas3.hpp>
#include <iostream>
/*
 * Routines of cblas level 3
 */
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
    // T=64 : 3 * 64^2 * 4 = 49152 bytes < 64 KiB L1d -> optimal

    for (rr = 0; rr < m; rr += Tr)
    for (dd = 0; dd < k; dd += Td)
    for (cc = 0; cc < n; cc += Tc)
    for (r = rr; r < std::min(rr+Tr, m); ++r)
    for (d = dd; d < std::min(dd+Td, k); ++d)
    {
        // A(r,d) invariant sur c -> mis en registre
        float Ard = alpha * A(r,d);
        // boucle interne sur c : stride-1 sur B(d,c) et C(r,c)
        // => vectorisable AVX 256 bits (8 floats par registre YMM)
        for (c = cc; c < std::min(cc+Tc, n); ++c)
            C(r,c) = beta * C(r,c) + Ard * B(d,c);
    }
}
