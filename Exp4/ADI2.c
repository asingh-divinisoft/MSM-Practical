#include <stdio.h>
#include <math.h>
#include "ADI2.h"
#include "io.h"
#define maxNodes 20
#define maxdt 40
int main()
{
	double L1, dt, lambda, dx, k;
	int n1, TN;
	double T[maxdt][maxNodes][maxNodes], t[5], data[10];
	double stiffness_matrix[maxNodes][maxNodes] = {0};
	double stiffness_Inv[maxNodes][maxNodes] = {0};
	//get data
	char input_filename[] = "ADI_input.txt";
	char ouput_filename[] = "ADI_output.txt";
	get_data(input_filename, data, 10);

	L1 = (int)data[0];
	dx = data[2];
	dt = data[3];
	TN = (int)(data[1] / dt);
	k = data[4];
	t[0] = data[5];
	t[1] = data[6];
	t[2] = data[7];
	t[3] = data[8];
	t[4] = data[9];
	//calculate lambda and others
	lambda = k * dt / (dx * dx);
	n1 = (int)(L1 / dx) - 1;
	printf("%lf \n%d\n%d", lambda, TN, n1);
	initialize_temp(T, n1, t);
	get_stiffness_matrix(stiffness_matrix, lambda, n1);
	get_mat_inverse(stiffness_matrix, stiffness_Inv, n1);
	solve_ADI(stiffness_Inv, T, n1, TN, lambda);
	//write data
	write_data(ouput_filename, T, n1, TN);
	return 0;
}