#include <mcblas3.hpp>
#include <iostream>
/*
 * Routines of cblas level 3
 */

void ssgemm(
    int m, int n, int k,
    float alpha,
    float ** A,
    float ** B,
    float beta,
    float ** C)
{
	// std::cout << "***************************************" << std::endl;
	// std::cout << "   WARNING: Not Yet Implemented..." << std::endl;
	// std::cout << "***************************************" << std::endl;

	int r, c, d;

	for (r = 0;  r < m; ++r)
	{
	  for (d = 0;  d < m; ++d)
	    {
	      for (c = 0;  c < n; ++c)
		{
		  C[r][c] = beta * C[r][c] + alpha * A[r][d] * B[d][c];
		}
	    }
	}
	
}
