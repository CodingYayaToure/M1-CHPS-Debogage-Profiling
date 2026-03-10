#pragma once

/*
 * Routines of cblas level 3
 */

/*
 * SSGEMM calcul C = beta * C + alpha * (A * B)
 * avec
 *       A (m,k)
 *       B (k,n)
 *       C (m,n)
 *
 */
void ssgemm(
    int m, int n, int k,
    float alpha,
    float ** A,
    float ** B,
    float beta,
    float ** C);
