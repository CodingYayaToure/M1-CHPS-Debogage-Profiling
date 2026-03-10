#include <mcblas3.hpp>
#include <iostream>
/*
 * Routines of cblas level 3
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

	// std::cout << "***************************************" << std::endl;
	// std::cout << "   WARNING: Not Yet Implemented..." << std::endl;
	// std::cout << "***************************************" << std::endl;

	int r, c, d;
	int rr, cc, dd;
	const int Tr = 32;
	const int Tc = 32;
	const int Td = 512;
	const int Uc = 4;
	const int Ur = 3;

//	float buffer[Td*Uc];


	if (alpha == 1.0f)
	{
		for (dd = 0;  dd < k; dd += Td)
		{
			for (c = 0;  c < n-(Uc-1); c += Uc)
			{
                // Copy Block of B into Buffer
				// for
				for(r = 0; r < m-(Ur-1); r += Ur)
				{
					float Cr0c0=0.0;
					float Cr0c1=0.0;
					float Cr0c2=0.0;
					float Cr0c3=0.0;

					float Cr1c0=0.0;
					float Cr1c1=0.0;
					float Cr1c2=0.0;
					float Cr1c3=0.0;


					for (d = dd;  d < std::min(dd+Td, k); ++d)
					{
						float Ar0d0;
						float Ar1d0;

						float Bd0c0;
						float Bd0c1;
						float Bd0c2;
						float Bd0c3;

						//t = t + A[r*n+d] * B[d*n+c];
						Ar0d0 = A(r+0,d+0);
						Ar1d0 = A(r+1,d+0);

						Bd0c0 = B(d+0,c+0);
						Bd0c1 = B(d+0,c+1);
						Bd0c2 = B(d+0,c+2);
						Bd0c3 = B(d+0,c+3);

						Cr0c0 = Cr0c0 + Ar0d0 * Bd0c0;
						Cr0c1 = Cr0c1 + Ar0d0 * Bd0c1;
						Cr0c2 = Cr0c2 + Ar0d0 * Bd0c2;
						Cr0c3 = Cr0c3 + Ar0d0 * Bd0c3;

						Cr1c0 = Cr1c0 + Ar1d0 * Bd0c0;
						Cr1c1 = Cr1c1 + Ar1d0 * Bd0c1;
						Cr1c2 = Cr1c2 + Ar1d0 * Bd0c2;
						Cr1c3 = Cr1c3 + Ar1d0 * Bd0c3;
					}
					C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
					C(r+0,c+1) = C(r+0,c+1) * beta + Cr0c1;
					C(r+0,c+2) = C(r+0,c+2) * beta + Cr0c2;
					C(r+0,c+3) = C(r+0,c+3) * beta + Cr0c3;

					C(r+1,c+0) = C(r+1,c+0) * beta + Cr1c0;
					C(r+1,c+1) = C(r+1,c+1) * beta + Cr1c1;
					C(r+1,c+2) = C(r+1,c+2) * beta + Cr1c2;
					C(r+1,c+3) = C(r+1,c+3) * beta + Cr1c3;

				}
				for (;  r < m; ++r)
				{
					float Cr0c0=0.0;
					float Cr0c1=0.0;
					float Cr0c2=0.0;
					float Cr0c3=0.0;
					for (d = dd;  d < std::min(dd+Td, k); ++d)
					{
						//t = t + A[r*n+d] * B[d*n+c];
						Cr0c0 = Cr0c0 + A(r,d) * B(d,c+0);
						Cr0c1 = Cr0c1 + A(r,d) * B(d,c+1);
						Cr0c2 = Cr0c2 + A(r,d) * B(d,c+2);
						Cr0c3 = Cr0c3 + A(r,d) * B(d,c+3);
					}
					C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
					C(r+0,c+1) = C(r+0,c+1) * beta + Cr0c1;
					C(r+0,c+2) = C(r+0,c+2) * beta + Cr0c2;
					C(r+0,c+3) = C(r+0,c+3) * beta + Cr0c3;
				}
			}
			for (;  c < n; ++c)
			{
                // Copy Block of B into Buffer
				// for
				for(r = 0; r < m-(Ur-1); r += Ur)
				{
					float Cr0c0=0.0;

					float Cr1c0=0.0;

					for (d = dd;  d < std::min(dd+Td, k); ++d)
					{
						float Ar0d0;
						float Ar1d0;

						float Bd0c0;
						//t = t + A[r*n+d] * B[d*n+c];
						Ar0d0 = A(r+0,d+0);
						Ar1d0 = A(r+1,d+0);

						Bd0c0 = B(d+0,c+0);

						Cr0c0 = Cr0c0 + Ar0d0 * Bd0c0;

						Cr1c0 = Cr1c0 + Ar1d0 * Bd0c0;

					}
					C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;

					C(r+1,c+0) = C(r+1,c+0) * beta + Cr1c0;

				}
				for (;  r < m; ++r)
				{
					float Cr0c0=0.0;
					for (d = dd;  d < std::min(dd+Td, k); ++d)
					{
						//t = t + A[r*n+d] * B[d*n+c];
						Cr0c0 = Cr0c0 + A(r,d) * B(d,c+0);
					}
					C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
				}
			}

		}



	}
	else // Alpha != 1.0f
	{
		for (rr = 0;  rr < m; rr += Tr)
		{
			for (dd = 0;  dd < k; dd += Td)
			{
				for (cc = 0;  cc < n; cc += Tc)
				{
					for (r = rr;  r < std::min(rr+Tr-1, m-1); r+=2)
					{
						for (c = cc;  c < std::min(cc+Tc-3, n-3); c+=4)
						{
							float Cr0c0=0.0;
							float Cr0c1=0.0;
							float Cr0c2=0.0;
							float Cr0c3=0.0;

							float Cr1c0=0.0;
							float Cr1c1=0.0;
							float Cr1c2=0.0;
							float Cr1c3=0.0;
							for (d = dd;  d < std::min(dd+Td, k); ++d)
							{
								//t = t + alpha * A[r*n+d] * B[d*n+c];
								Cr0c0 = Cr0c0 + alpha * A(r+0,d) * B(d,c+0);
								Cr0c1 = Cr0c1 + alpha * A(r+0,d) * B(d,c+1);
								Cr0c2 = Cr0c2 + alpha * A(r+0,d) * B(d,c+2);
								Cr0c3 = Cr0c3 + alpha * A(r+0,d) * B(d,c+3);

								Cr1c0 = Cr1c0 + alpha * A(r+1,d) * B(d,c+0);
								Cr1c1 = Cr1c1 + alpha * A(r+1,d) * B(d,c+1);
								Cr1c2 = Cr1c2 + alpha * A(r+1,d) * B(d,c+2);
								Cr1c3 = Cr1c3 + alpha * A(r+1,d) * B(d,c+3);
							}
							C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
							C(r+0,c+1) = C(r+0,c+1) * beta + Cr0c1;
							C(r+0,c+2) = C(r+0,c+2) * beta + Cr0c2;
							C(r+0,c+3) = C(r+0,c+3) * beta + Cr0c3;

							C(r+1,c+0) = C(r+1,c+0) * beta + Cr1c0;
							C(r+1,c+1) = C(r+1,c+1) * beta + Cr1c1;
							C(r+1,c+2) = C(r+1,c+2) * beta + Cr1c2;
							C(r+1,c+3) = C(r+1,c+3) * beta + Cr1c3;
						}
						for (;  c < std::min(cc+Tc, n); ++c)
						{
							float Cr0c0=0.0;
							float Cr1c0=0.0;
							for (d = dd;  d < std::min(dd+Td, k); ++d)
							{
								//t = t + alpha * A[r*n+d] * B[d*n+c];
								Cr0c0 = Cr0c0 + alpha * A(r+0,d) * B(d,c+0);
								Cr1c0 = Cr1c0 + alpha * A(r+1,d) * B(d,c+0);
							}
							C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
							C(r+1,c+0) = C(r+1,c+0) * beta + Cr1c0;
						}
					}
					for (;  r < std::min(rr+Tr, m); ++r)
					{
						for (c = cc;  c < std::min(cc+Tc-3, n-3); c+=4)
						{
							float Cr0c0=0.0;
							float Cr0c1=0.0;
							float Cr0c2=0.0;
							float Cr0c3=0.0;
							for (d = dd;  d < std::min(dd+Td, k); ++d)
							{
								//t = t + alpha * A[r*n+d] * B[d*n+c];
								Cr0c0 = Cr0c0 + alpha * A(r,d) * B(d,c+0);
								Cr0c1 = Cr0c1 + alpha * A(r,d) * B(d,c+1);
								Cr0c2 = Cr0c2 + alpha * A(r,d) * B(d,c+2);
								Cr0c3 = Cr0c3 + alpha * A(r,d) * B(d,c+3);
							}
							C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
							C(r+0,c+1) = C(r+0,c+1) * beta + Cr0c1;
							C(r+0,c+2) = C(r+0,c+2) * beta + Cr0c2;
							C(r+0,c+3) = C(r+0,c+3) * beta + Cr0c3;
						}
						for (;  c < std::min(cc+Tc, n); ++c)
						{
							float Cr0c0=0.0;
							for (d = dd;  d < std::min(dd+Td, k); ++d)
							{
								//t = t + alpha * A[r*n+d] * B[d*n+c];
								Cr0c0 = Cr0c0 + alpha * A(r,d) * B(d,c+0);
							}
							C(r+0,c+0) = C(r+0,c+0) * beta + Cr0c0;
						}
					}
				}
			}
		}
	}
}
