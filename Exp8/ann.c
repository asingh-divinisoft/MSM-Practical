#include <stdio.h>
#include <math.h>
#include "mat_operations.h"
#include "ann.h"
#include "io.h"

int main()
{
	char output_file[] = "output.txt";
	//double W[20][20] = { {-0.978340, -2.499652} };
	//double V[20][20] = { {-15.877567, 0.139212}, {28.331367, -7.525458} };
	double W[20][20] = {{0.2, -0.5}};
	double V[20][20] = {{0.1, 0.4}, {-0.2, 0.2}};
	double delta_W[20][20] = {{0, 0}};
	double delta_V[20][20] = {{0, 0}, {0, 0}};

	double inputs[2][20] = {{0.4, 0.3, 0.6, 0.2, 0.1}, {-0.7, -0.5, 0.1, 0.4, -0.2}};
	double targets[5] = {0.1, 0.05, 0.3, 0.25, 0.12};
	double outputs[20][20];

	// double ip[20][20], op=targets[0];
	// ip[0][0] = inputs[0][0];
	// ip[1][0] = inputs[1][0];
	// step(ip, op, V, W, delta_W, delta_V, 0.9);
	train(inputs, targets, V, W, delta_W, delta_V, 0.0, 0.01, 5);
	// mat2d_print(W, 1, 2);
	// mat2d_print(V, 2, 2);
	predict(inputs, outputs, V, W, 5);
	mat2d_print(outputs, 1, 5);

	double arr[20][20];
	arr[0][0] = W[0][0];
	arr[0][1] = W[0][1];
	arr[1][0] = V[0][0];
	arr[1][1] = V[0][1];
	arr[2][0] = V[1][0];
	arr[2][1] = V[1][1];
	writedata(output_file, arr, 3, 2);
	return 0;
}
