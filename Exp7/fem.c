#include <stdio.h>
#include "gauss_elimination.h"
#include <math.h>
#include "io.h"
#include "fem.h"
int main(){
	double data[2], output[5];
	char input_filename[] = "input.txt";
	char output_filename[] = "output.txt";
	getdata(input_filename, data, 5);
	double t1 = data[0], t2 = data[1];
	solve(t1, t2, output);
	writedata(output_filename, output, 5);
}
