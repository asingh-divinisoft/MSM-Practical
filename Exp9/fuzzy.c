#include <stdio.h>
#include <math.h>
#include "io.h"
#include "fuzzy.h"
#include "defuzzify.h"

int main()
{
	char in_filename[] = "input.txt";
	char out_filename[] = "output.txt";
	int i, n=0;
	double inputs[50][3], outputs[50];
	get_data(in_filename, inputs, &n);
	
	double mem[3][3];
	double y[9];

	for (i = 0; i < n; ++i)
	{
		//fuzzification
		membership(inputs[i][0], 0, mem[0]);
		membership(inputs[i][1], 1, mem[1]);
		membership(inputs[i][2], 2, mem[2]);

		//Rule step evaluation
		apply_rules(mem, y);
		int j=0;
		for (j = 0; j < 9; ++j)
		{
			//printf("%lf\n", y[j]);
		}
		//Defuzzification
		outputs[i] = defuzzify(y);
		//printf("%lf\n", outputs[i]);
	}

	write_data(out_filename, outputs, n);
	return 0;
}
