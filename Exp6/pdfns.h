#include <math.h>
#include "gauss_elimination.h"
#define max 100

void get_ab(double s[2], double w[2], double t[2], double a[2][20], double b[20], double x_a, double x_b, double T, double lambda)
{
        double R = 8.314, d_mu_a, d_mu_b, d_mu_a_dxa, d_mu_a_dxb, d_mu_b_dxa, d_mu_b_dxb;
        d_mu_a = (t[0] - T) * s[0] + x_b * x_b * w[1] - x_a * x_a * w[0] + R * T * log(1 - x_b) - R * T * log(1 - x_a);
        d_mu_b = (t[1] - T) * s[1] + (1 - x_b) * (1 - x_b) * w[1] - (1 - x_a) * (1 - x_a) * w[0] + R * T * log(x_b) - R * T * log(x_a);
        d_mu_a_dxa = -2 * x_a * w[0] + R * T / (1 - x_a);
        d_mu_a_dxb = 2 * x_b * w[1] - R * T / (1 - x_b);
        d_mu_b_dxa = 2 * (1 - x_a) * w[0] - R * T / x_a;
        d_mu_b_dxb = -2 * (1 - x_b) * w[1] + R * T / x_b;

        a[0][0] = (1 + lambda) * d_mu_a_dxa;
        a[0][1] = d_mu_a_dxb;
        a[1][0] = d_mu_b_dxa;
        a[1][1] = (1 + lambda) * d_mu_b_dxb;
        b[0] = -d_mu_a;
        b[1] = -d_mu_b;
}

void nr2d(double s[2], double w[2], double t[2], double x[2], double T, double lambda, double factor)
{
        double a[2][20], dx[20], b[20], error[2];
        //get initial values of xa and xb from the isog output
        error[0] = 10;
        error[1] = 10;
        while (error[0] > 0.000001 && error[1] > 0.000001)
        {
                get_ab(s, w, t, a, b, x[0], x[1], T, lambda);
                gauss_elimination(a, b, dx, 2);
                x[0] += dx[0];
                x[1] += dx[1];
                error[0] = fabs(dx[0]) / x[0];
                error[1] = fabs(dx[1]) / x[1];
                lambda /= factor;
        }
}

void get_phase_diagram(double left[max][2], double right[max][2], int n, int idx, double s[2], double w[2], double t[2], double pd_data[max][3], double lambda, double factor)
{
        int i = 0, j = 0;
        double x[2], T;
        // congruent maxima
        for (i = 0; i < idx; i++)
        {
                x[0] = left[i][0];
                x[1] = left[i][0];
                T = left[i][1];
                nr2d(s, w, t, x, T, lambda, factor);
                pd_data[i][0] = T;
                pd_data[i][1] = x[0];
                pd_data[i][2] = x[1];
        }
        for (i = idx, j = 0; i < n - 1; i++, j++)
        {
                x[0] = right[j][0];
                x[1] = right[j][0];
                T = right[j][1];
                nr2d(s, w, t, x, T, lambda, factor);
                pd_data[i][0] = T;
                pd_data[i][1] = x[0];
                pd_data[i][2] = x[1];
        }
}
