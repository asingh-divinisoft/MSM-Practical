#define R 8.3144

double g_mix(double coeff[6], double t, double xb);
double g_id(double t, double xb);
double rk_evaluate(double coeff[6], double t, double xb);
double g_mix(double coeff[6], double t, double xb)
{
	double gid, gxs;
	gid = g_id(t, xb);
	gxs = rk_evaluate(coeff, t, xb);
	return (gid + gxs);
}
double g_id(double t, double xb)
{
	return (R * t * ((1 - xb) * log(1 - xb) + xb * log(xb)));
}
//evaluate the r-k polynomila with the coefficeints coeff at the given temp. t and composition xb
double rk_evaluate(double coeff[6], double t, double xb)
{
	int i = 0;
	double gxs = 0.0;
	for (i = 0; i <= 5; i += 2)
	{
		gxs = gxs + (coeff[i] + coeff[i + 1] * t) * pow((1 - 2 * xb), (i / 2));
	}
	gxs = xb * (1 - xb) * gxs;
	return (gxs);
}
