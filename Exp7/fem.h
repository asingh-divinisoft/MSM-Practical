void solve(double T1, double T5, double output[5])
{
	double A[5][5] = {{1, -0.4, 0, 0, 0}, {0, 0.8, -0.4, 0, 0}, {0, -0.4, 0.8, -0.4, 0}, {0, 0, -0.4, 0.8, 0}, {0, 0, 0, -0.4, -1}};
	double B[5] = {12.5, 25, 25, 25, 12.5};
	B[0] += -0.4 * T1;
	B[1] += 0.4 * T1;
	B[3] += 0.4 * T5;
	B[4] += -0.4 * T5;
	gauss_elimination(A, B, output, 5);
}
