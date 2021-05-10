typedef struct triangle
{
	double area;
	double com;
} triangle;

triangle getTriangle(double truth_value, int index)
{
	triangle X;
	double base = 8.64;

	if (index == 0)
	{
		X.area = base / 4 * truth_value * (2 - truth_value);
		X.com = 59.5 + base / 2 - (base / 6 * ((3 - truth_value * truth_value) / (2 - truth_value)));
	}
	else if (index == 8)
	{
		X.area = base / 4 * truth_value * (2 - truth_value);
		X.com = 59.5 + 7 * base / 2 + (base / 6 * ((3 - truth_value * truth_value) / (2 - truth_value)));
	}
	else
	{
		X.area = base / 2 * truth_value * (2 - truth_value);
		X.com = 59.5 + index * (base / 2);
	}

	return X;
}

double defuzzify(double hardness[9])
{
	triangle tarr[9];

	int i = 0;
	for (i = 0; i < 9; i++)
	{
		tarr[i] = getTriangle(hardness[i], i);
	}

	//Total mass
	double total_area = 0;
	for (i = 0; i < 9; i++)
	{
		total_area += tarr[i].area;
	}

	//Finding weighted sum of centroids
	double wsc = 0;
	for (i = 0; i < 9; ++i)
	{
		wsc += tarr[i].area * tarr[i].com;
		//printf("%lf %lf, %lf\n", wsc, tarr[i].area, tarr[i].com);
	}

	//COM
	return wsc / total_area;
}
