//---ORIGINAL : CODE DE DEPART-----------------

// #include <mcblas3.hpp>
// #include <iostream>
// /*
//  * Routines of cblas level 3
//  */

// void ssgemm(
//     int m, int n, int k,
//     float alpha,
//     float ** A,
//     float ** B,
//     float beta,
//     float ** C)
// {
// 	// std::cout << "***************************************" << std::endl;
// 	// std::cout << "   WARNING: Not Yet Implemented..." << std::endl;
// 	// std::cout << "***************************************" << std::endl;

// 	int r, c, d;
// 	int rr, cc, dd;
// 	const int Tr = 128;
// 	const int Tc = 128;
// 	const int Td = 128;

// 	for (rr = 0;  rr < m; rr += Tr)
// 	{
// 		for (dd = 0;  dd < m; dd += Td)
// 		{
// 			for (cc = 0;  cc < m; cc += Tc)
// 			{
// 				for (c = cc;  c < std::min(cc+Tc, n); ++c)
// 				{
// 					for (r = rr;  r < std::min(rr+Tr ,m); ++r)
// 					{
// 						float t=0.0;
// 						for (d = dd;  d < std::min(dd+Td, m); ++d)
// 						{
// 							t = t + alpha * A[r][d] * B[d][c];
// 						}
// 						C[r][c] = C[r][c] * beta + t;
//  					}
// 				}
// 			}
// 		}
// 	}

// }

//-------------OUVEAU CODE -----------


#include <mcblas3.hpp>
#include <iostream>

void ssgemm(
    int m, int n, int k,
    float alpha,
    float ** A,
    float ** B,
    float beta,
    float ** C)
{
    int r, c, d;
    int rr, cc, dd;
    const int Tr = 128;
    const int Tc = 128;
    const int Td = 128;

    for (rr = 0; rr < m; rr += Tr)
    {
        for (dd = 0; dd < m; dd += Td)
        {
            for (cc = 0; cc < n; cc += Tc)
            {
                for (r = rr; r < std::min(rr+Tr, m); ++r)
                {
                    for (d = dd; d < std::min(dd+Td, m); ++d)
                    {
                        for (c = cc; c < std::min(cc+Tc, n); ++c)
                        {
                            C[r][c] = beta * C[r][c] + alpha * A[r][d] * B[d][c];
                        }
                    }
                }
            }
        }
    }
}