#define R 8.3144

double g_id(double t, double xb);
double rk_evaluate(double coeff[6], double t, double xb);
double g_mix(double coeff[6], double t, double xb);

/**
 * @brief  Ideal Gibbs Free Energy
 * @note   For binary solution
 * @param  t: Temperature in K
 * @param  xb: Mole Fraction of solute
 * @retval g_id: double
 */
double g_id(double t, double xb)
{
	return (R * t * ((1 - xb) * log(1 - xb) + xb * log(xb)));
}

/**
 * @brief  Excess Gibbs Free Energy
 * @note   r-k polynomila with the coefficeints coeff at the given temp. t and composition xb
 * @param  coeff[6]: a1, b1, a2, b2, a3, b3
 * @param  t: Temperature in K
 * @param  xb: Mole Fraction of solute in binary solution
 * @retval g_xs
 */
double rk_evaluate(double coeff[6], double t, double xb)
{
	int i = 0;
	double gxs = 0.0;
	for (i = 0; i <= 5; i += 2) // NOTE: i += 2
	{
		gxs += (coeff[i] + coeff[i + 1] * t) * pow((1 - 2 * xb), (i / 2));
	}
	gxs *= xb * (1 - xb);
	return gxs;
}

/**
 * @brief  Gibbs Free Energy of Mixing
 * @note   
 * @param  coeff[6]: a1, b1, a2, b2, a3, b3
 * @param  t: Temperature in K
 * @param  xb: Mole Fraction of solute in binary solution
 * @retval 
 */
double g_mix(double coeff[6], double t, double xb)
{
	double gid, gxs;
	gid = g_id(t, xb);
	gxs = rk_evaluate(coeff, t, xb);
	return (gid + gxs);
}