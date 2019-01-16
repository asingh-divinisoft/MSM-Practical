//include header files required
#include "gauss_elimination.h"
//other definitions if any
//prototype declarations
#define maxNodes 20
#define maxdt 40

void get_stiffness_matrix(double a[maxNodes][maxNodes],double lambda, int n)
{
  int i=0,j=0;
  for(j=0; j<n; j++){
      for(i=0; i<n; i++){
        a[j][i] = 0;
      }
  }

  a[0][0] = 2*(1 + lambda);
  a[0][1] = -lambda;


  a[n-1][n-2] = -lambda;
  a[n-1][n-1] = 2*(1 + lambda);

  for(j=0; j<n; j++){
    a[j][j-1] = -lambda;
    a[j][j] = 2*(1 + lambda);
    a[j][j+1] = -lambda;
  }

    
}

void get_mat_inverse(double a[maxNodes][maxNodes], double a_inv[maxNodes][maxNodes], int n)
{
  int i=0, j=0;
  double b[maxNodes], x[maxNodes];
  // A * A_inv = I
  for (i = 0; i < n; ++i)
  {
    // take a row of a and create b corresponding to row index
    for (j = 0; j < n; ++j)
    {
      b[j] = 0;
    }
    b[i] = 1;
    //now solve for the corresponding column of a_inv
    gauss_elimination(a, b, x, n);
    for (j = 0; j < n; ++j)
    {
      a_inv[j][i] = x[j];
    }
  }
}

void initialize_temp(double T[maxdt][maxNodes][maxNodes],int n, double t[5])
{
  int i=0,j=0, k=0;
  for(k=0; k<maxdt; k++){
    for (i = 0; i <n+2 ; ++i)
    {
      for (j = 0; j <n+2 ; ++j)
      {
        T[k][i][j] = t[4];
        if (i==0)
        {
          T[k][i][j] = t[1];
        } 
        else if (i==n+1){
          T[k][i][j] = t[3];
        }
        if (j==0){
          T[k][i][j] = t[0];
        }
        else if (j==n+1){
          T[k][i][j] = t[2];
        }
      }
    }
  }

}
void initialize_T0(double T0[maxNodes][maxNodes],double T[maxdt][maxNodes][maxNodes],int n, int xn)
{ //update T0 with the nth layer of T
int i=0,j=0;
  for(i=0; i<xn+2; i++){
    for(j=0; j<xn+2; j++){
      T0[i][j] = T[n][i][j];
    }
  }
}

void mat_multi_square_column(double a_inv[maxNodes][maxNodes],double b[maxNodes], int n)
{ //multiply a and b having length n
  double x[maxNodes];
  for (int i = 0; i < n; ++i)
  {
    x[i] = 0;
    for (int j = 0; j < n; ++j)
    {
      x[i] += a_inv[i][j] * b[j];
    }
  }
  for (int i = 0; i < n; ++i)
  {
    b[i] = x[i];
  }
}

void update_T0_1(double T0[maxNodes][maxNodes],double b[maxNodes], int column,int n)
{ //update the column of T0 with b of length n in the position ‘column’
  int i=0;
  for(i=1; i<=n; i++){
    T0[i][column] = b[i-1];
  }
}
void update_T0_2(double T0[maxNodes][maxNodes],double b[maxNodes], int row,int n)
{ //update the row of T0 with b of length n in the position ‘row’
  int j=0;
  for(j=1; j<=n; j++){
    T0[row][j] = b[j-1];
  }
}

void updateT(double T[maxdt][maxNodes][maxNodes],double T0[maxNodes][maxNodes],int n,int xn)
{ //update nth layer of T with T0 matrix of length n
  int i=0,j=0;
  for(i=1; i<=xn; i++){
    for(j=1; j<=xn; j++){
      T[n][i][j] = T0[i][j];
    }
  }
}
void solve_ADI(double a_inv[maxNodes][maxNodes], double T[maxdt][maxNodes][maxNodes], int xn, int tn,double lambda)
{
  int i,j,t;
  double T0[maxNodes][maxNodes]={0};
  double b[maxNodes]={0};
  for(t=1;t<=tn;t++)
  {
    //initializing middle time layer temp profile
    initialize_T0(T0,T,t-1,xn);
    //frame the a matrix for first direction
    for(i=1;i<=xn;i++)
    {
      //frame b matrix
      b[0] = lambda*T0[1][i-1] + 2*(1-lambda)*T0[1][i] + lambda*T0[1][i+1] + lambda*T0[0][i];
      for(j=1; j<xn-1; j++){
        b[j] = lambda*T0[j+1][i-1] + 2*(1-lambda)*T0[j+1][i] + lambda*T0[j+1][i+1];
      }
      b[xn-1] = lambda*T0[j+1][i-1] + 2*(1-lambda)*T0[j+1][i] + lambda*T0[j+1][i+1] + lambda*T0[xn+1][i];
      //Lets solve the equations
      mat_multi_square_column(a_inv,b,xn);
      //update b values to the T0 matrix
      update_T0_1(T0,b,i,xn);
    }
    //frame the a matrix for second direction
    for(j=1;j<=xn;j++)
    {
      //frame b matrix
      b[0] = lambda*T0[j-1][1] + 2*(1-lambda)*T0[j][1] + lambda*T0[j+1][1] + lambda*T0[j][0];
      for(i=1; i<xn-1; i++){
        b[j] = lambda*T0[j-1][i+1] + 2*(1-lambda)*T0[j][i+1] + lambda*T0[j+1][i+1];
      }
      b[xn-1] = lambda*T0[j-1][i+1] + 2*(1-lambda)*T0[j][i+1] + lambda*T0[j+1][i+1] + lambda*T0[j][xn+1];
      //Lets solve the equations
      mat_multi_square_column(a_inv,b,xn);
      //update b values to the T0 matrix
      update_T0_2(T0,b,j,xn);
    }
    updateT(T,T0,t,xn);
  }
}