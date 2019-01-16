void membership(double x, int num, double mem[3]){
	double mid=0, slope=0;
	if(num == 0){
		mid = 3; slope = 1;
	}
	if(num == 1){
		mid = 1150; slope = 0.01;
	}
	if(num == 2){
		mid = 1.5; slope = 2;
	}
	//degree for small
	if(x < mid){
		mem[0] = slope*(mid - x);
	} else { mem[0] = 0; }

	//degree for medium
	if(x < mid){
		mem[1] = slope*(x - mid) + 1;
	} else { mem[1] = 1 + slope*(mid - x); }

	//degree for large
	if(x >= mid){
		mem[2] = slope*(x - mid);
	} else { mem[2] = 0; }
}

double min(double a, double b, double c){
	//find minimum of three memberships
	a = a < b ? a : b;
	return a < c ? a : c;
}

double max(double *arr, int n){
	int i;
	double m = *arr;
	for (i = 1; i < n; ++i)
	{
		if( m < *(arr + i) ){
			m = *(arr + i);
		}
	}
	return m;
}

double evaluate(double mem[3][3], int x1, int x2, int x3){
	return min(mem[0][x1], mem[1][x2], mem[2][x3]);
}

void merge_rules(double y[15], double output[9]){
	output[0] = y[0];
	output[1] = y[1];
	output[2] = y[2];
	output[3] = 0;
	output[4] = y[3];
	output[5] = max(&y[4], 3);
	output[6] = max(&y[7], 4);
	output[7] = max(&y[11], 2);
	output[8] = max(&y[13], 2);
}

void apply_rules(double mem[3][3], double y[8]){
	//Rule 1
	double output[15];
	output[0] = evaluate(mem, 1, 0, 1); //SS
	output[1] = evaluate(mem, 2, 0, 0); //VS
	output[2] = evaluate(mem, 2, 0, 2); //S
	output[3] = evaluate(mem, 0, 0, 0);  //M
	output[4] = evaluate(mem, 2, 1, 1); //ML
	output[5] = evaluate(mem, 0, 0, 2); //ML
	output[6] = evaluate(mem, 0, 2, 2); //ML
	output[7] = evaluate(mem, 1, 1, 0);  //L
	output[8] = evaluate(mem, 0, 2, 0);  //L
	output[9] = evaluate(mem, 2, 2, 0);  //L
	output[10] = evaluate(mem, 2, 2, 2); //L
	output[11] = evaluate(mem, 1, 1, 1); //VL
	output[12] = evaluate(mem, 1, 1, 2); //VL
	output[13] = evaluate(mem, 0, 1, 1); //LL
	output[14] = evaluate(mem, 1, 2, 1); //LL
	merge_rules(output, y);
}
