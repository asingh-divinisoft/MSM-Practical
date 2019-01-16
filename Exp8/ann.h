#define max 20
double sigmoid(double n){
        return 1/(1+pow(2.718282, -n));
}

void sig_matrix(double a[max][max], double b[max][max], int ac, int ar){
        int i, j;
        for(i=0; i<ac; i++){
                for(j=0; j<ar; j++){
                        b[i][j] = sigmoid(a[i][j]);
                }
        }
}

void reciprocal(double a[max][max], int ac, int ar, double factor){
        int i, j;
        for(i=0; i<ac; i++){
                for(j=0; j<ar; j++){
                        a[i][j] = factor / a[i][j];
                }
        }
}

void forward_prop(double inputs[max][max], double target, double W[max][max], double V[max][max], double *Error, double O_o[max][max], double O_h[max][max]){
        double V_t[max][max], I_h[max][max], I_o[max][max];

        // V_t = transpose of V
        V_t[0][0] = V[0][0];
        V_t[0][1] = V[1][0];
        V_t[1][0] = V[0][1];
        V_t[1][1] = V[1][1];

        // I_h = V_t * O_i
        mat2d_mat2d_multiplication(V_t, inputs, I_h, 2, 2, 2, 1);

        // O_h = sigmoid(I_h)
        sig_matrix(I_h, O_h, 2, 1);

        // I_o = W * O_h
        mat2d_mat2d_multiplication(W, O_h, I_o, 1, 2, 2, 1);
        sig_matrix(I_o, O_o, 1, 1);

        //Error
        *Error = target - O_o[0][0];
}

void back_prop(double inputs[max][max], double W[max][max], double V[max][max], double delta_V[max][max], double delta_W[max][max], double *Error, double O_o[max][max], double O_h[max][max], double alpha, double factor){
        //derivative d
        double Y[2], eta=0.99;
	double d, e[2];
	double d_[max][max], X[max][max];

        d = (*Error) * O_o[0][0] * ( 1 - O_o[0][0] );

        // Y = O_h * d
        Y[0] = O_h[0][0] * d;
        Y[1] = O_h[1][0] * d;

        Y[0] = factor / Y[0];
        Y[1] = factor / Y[1];

        // delta_W = alpha * delta_W + eta * Y;
        delta_W[0][0] = alpha * delta_W[0][0] + eta * Y[0];
        delta_W[0][1] = alpha * delta_W[0][1] + eta * Y[1];

        // e = W * d
        e[0] = W[0][0] * d;
        e[1] = W[0][1] * d;

        //d* = e * Oh * (1-Oh)
        d_[0][0] = e[0] * O_h[0][0] * (1 - O_h[0][0]);
        d_[0][1] = e[1] * O_h[1][0] * (1 - O_h[1][0]);

        // X = O_i * d*
        mat2d_mat2d_multiplication(inputs, d_, X, 2, 1, 1, 2);
        reciprocal(X, 2, 2, factor);

        // delta_V = alpha * delta_v + eta * X
        mat2d_scalar_multiplication(delta_V, alpha, 2, 2);
        mat2d_scalar_multiplication(X, eta, 2, 2);
        mat2d_mat2d_addition(delta_V, X, delta_V, 2, 2, 2, 2);
	
	// mat2d_print(delta_W, 1, 2);
	//mat2d_print(delta_V, 2, 2);
        // W = W + delta_W
        // V = V + delta_V
        mat2d_mat2d_addition(W, delta_W, W, 1, 2, 1, 2);
        mat2d_mat2d_addition(V, delta_V, V, 2, 2, 2, 2);

}

void train(double inputs[2][max], double outputs[max], double V[max][max], double W[max][max], double delta_W[max][max], double delta_V[max][max], double alpha, double Err, int n){
        double ip[max][max], op, er;
        int i;
        double error_var, O_h[max][max], O_o[max][max];
        double factor = 0.001;
        double fac = 2;

        er = 1;
	
        while(er > Err){
                er = 0;
                for(i=0; i<n; i++){
			error_var = 0;
                        ip[0][0] = inputs[0][i];
                        ip[1][0] = inputs[1][i];
                        op = outputs[i];
                        forward_prop(ip, op, W, V, &error_var, O_o, O_h);
			back_prop(ip, W, V, delta_V, delta_W, &error_var, O_o, O_h, alpha, factor);
                        if(factor > 0.000000001)
                                factor /= fac; fac*= 2;
                        er += pow(error_var, 2);
                }
                er = sqrt(er);
                er /= (n-1);
                printf("%lf \n", er);
                //mat2d_print(W, 1, 2);
        }
}

void predict(double inputs[2][max], double outputs[max][max], double V[max][max], double W[max][max], int n){
        double V_t[max][max], I_h[max][max], I_o[max][max], O_o[max][max], ip[max][max];
        int i;
        double O_h[max][max];

        // V_t = transpose of V
        V_t[0][0] = V[0][0];
        V_t[0][1] = V[1][0];
        V_t[1][0] = V[0][1];
        V_t[1][1] = V[1][1];

        for (i = 0; i < n; ++i)
        {
                ip[0][0] = inputs[0][i];
                ip[1][0] = inputs[1][i];
                // I_h = V_t * O_i
                mat2d_mat2d_multiplication(V_t, ip, I_h, 2, 2, 2, 1);

                // O_h = sigmoid(I_h)
                sig_matrix(I_h, O_h, 2, 1);

                // I_o = W * O_h
                mat2d_mat2d_multiplication(W, O_h, I_o, 1, 2, 2, 1);
                sig_matrix(I_o, O_o, 1, 1);

                outputs[0][i] = O_o[0][0];
        }

}
