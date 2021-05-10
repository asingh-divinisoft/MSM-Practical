#include <stdio.h>
#include "io.h"
#include "pdfns.h"

#define max 100
int main()
{
	double S[2], T[2], W[2], dxb, lambda, factor;
	int n;
	double isog_left[max][2], isog_right[max][2], data[20], pd_data[max][3];
	char input_file[] = "pd_input.txt";
	char isog_file[] = "isog.txt";
	char output_file[] = "pd_output.txt";
	//get the data
	getdata(input_file, data, 9);

	n = (int)data[0];
	S[0] = data[1];
	S[1] = data[2];
	T[0] = data[3];
	T[1] = data[4];
	W[0] = data[5];
	W[1] = data[6];
	lambda = data[7];
	factor = data[8];
	dxb = 1.0 / (n + 1);

	int idx = getisog(isog_file, isog_left, isog_right, n);

	get_phase_diagram(isog_left, isog_right, n, idx, S, W, T, pd_data, lambda, factor);
	writedata(output_file, pd_data, n); //write the data to the outputfile
	return 0;
}
