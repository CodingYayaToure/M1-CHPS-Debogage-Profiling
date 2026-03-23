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
    float * A,
    float * B,
    float beta,
    float * C)
{

	// std::cout << "***************************************" << std::endl;
	// std::cout << "   WARNING: Not Yet Implemented..." << std::endl;
	// std::cout << "***************************************" << std::endl;

	int r, c, d;
	int rr, cc, dd;

	const int Tr = 64;
	const int Tc = 64;
	const int Td = 64;


	for (rr = 0;  rr < m; rr += Tr)
	{
		for (dd = 0;  dd < k; dd += Td)
		{
			for (cc = 0;  cc < m; cc += Tc)
			{
				for (r = rr;  r < std::min(rr+Tr, m); ++r)
				{
					for (c = cc;  c < std::min(cc+Tc, n); ++c)
					{
						float t=0.0;
						for (d = dd;  d < std::min(dd+Td, k); ++d)
						{
							//t = t + alpha * A[r*k+d] * B[d*n+c];
							t = t + alpha * A(r,d) * B(d,c);
						}
						// C[r*n+c] = C[r*n+d] *beta + t;
						C(r,c) = C(r,c) * beta + t;
					}
				}
			}
		}
	}
	// for (r = 0;  r < m; ++r)
	// {
	//   for (d = 0;  d < k; ++d)
	//   {
	//       for (c = 0;  c < n; ++c)
	// 	{
	// 	  C(r,c) = beta * C(r,c) + alpha * A(r,d) * B(d,c);
	// 	}
	//   }
	// }

}
